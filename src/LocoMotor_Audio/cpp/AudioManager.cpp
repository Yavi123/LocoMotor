#include "AudioManager.h"
#include "AudioListener.h"
#include "fmod.hpp"
#include "fmod_studio.hpp"
#include "fmod_errors.h"

#include "Json/JSON.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <cassert>

using namespace LocoMotor;
using namespace LocoMotor::Audio;

AudioManager* AudioManager::_instance = nullptr;

bool AudioManager::Init()
{
	return Init(16, true);
}

bool AudioManager::Init(const Json::JSONObject& audioData) {

	int desiredNumChannels = 16;
	bool usingStudio = true;

	Json::JSONValue* numChannels = audioData.at("Num_channels");
	if (numChannels != nullptr) {
		if (numChannels->IsNumber()) {
			desiredNumChannels = (int)numChannels->AsNumber();
		}
	}

	Json::JSONValue* initStudio = audioData.at("Init_studio");
	if (initStudio != nullptr) {
		if (initStudio->IsBool()) {
			usingStudio = initStudio->AsBool();
		}
		else if (initStudio->IsNumber()) {
			usingStudio = (initStudio->AsNumber() > 0.5f) ? true : false;
		}
	}

	return Init(desiredNumChannels, usingStudio);
}

bool AudioManager::Init(int numChannels, bool initialiseStudio) {
	assert(_instance == nullptr);
	_instance = new AudioManager();

	if (!_instance->init(numChannels, initialiseStudio)) {
		delete _instance;
		_instance = nullptr;
		return false;
	}

	return true;
}

AudioManager* AudioManager::GetInstance()
{
	assert(_instance != nullptr);
	return _instance;
}

void AudioManager::Release()
{
	assert(_instance != nullptr);
	delete _instance;
	_instance = nullptr;
}

unsigned short AudioManager::update()
{
	return _studioSys? _studioSys->update() : _sys->update();
}

unsigned short AudioManager::addSound(const char* fileName, bool ui)
{
	if (_soundLib[fileName] != nullptr) {
		if (ui)
			_soundLib[fileName]->setMode(FMOD_DEFAULT);
		else
			_soundLib[fileName]->setMode(FMOD_3D_WORLDRELATIVE);
		return 0;
	}

#ifndef _DEBUG
	if (ui)
		return _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[fileName]);
	else
		return _sys->createSound(fileName, FMOD_3D_WORLDRELATIVE, nullptr, &_soundLib[fileName]);
#endif // _DEBUG

#ifdef _DEBUG
	FMOD_RESULT err;
	if (ui)
		err = _sys->createSound(fileName, FMOD_DEFAULT, nullptr, &_soundLib[fileName]);
	else
		err = _sys->createSound(fileName, FMOD_3D_WORLDRELATIVE, nullptr, &_soundLib[fileName]);

	if (err != 0) {
		std::cerr << "\033[1;31m" << "AUDIO: File '" << fileName << "' wasn't found or is not valid" << "\033[0m" << std::endl;
	}
	return err;
#endif // _DEBUG
}

unsigned short AudioManager::playSound(const char* id)
{
	FMOD::Channel* ch;
	unsigned short err = playSoundwChannel(id, &ch);
	ch->setPaused(false);
	return err;
}

unsigned short AudioManager::playSoundwChannel(const char* id, FMOD::Channel** channel)
{
#ifndef _DEBUG
	unsigned short err = _sys->playSound(_soundLib[id], _main, true, channel);

	return err;
#endif // _DEBUG

#ifdef _DEBUG
	FMOD_RESULT err = _sys->playSound(_soundLib[id], _main, true, channel);

	if (err != 0) {
		std::cerr << "\033[1;31m" << "AUDIO: Trying to play sound '" << id << "' caused fmod exception: " << FMOD_ErrorString(err) << "\033[0m" << std::endl;
	}
	return err;
#endif // _DEBUG
}

void LocoMotor::Audio::AudioManager::loadFMODBuild(const char* fmodPath) {

	if (_studioSys == nullptr) {
	#ifdef _DEBUG
		std::cerr << "\033[1;31m" << "Studio not initialized, pass a 'true' to the Init to initialize with Studio" << "\033[0m" << std::endl;
	#endif
		return;
	}

	FMOD::Studio::Bank* bank;
	std::string masterStringPath = fmodPath;
	masterStringPath += "/Master.strings.bank";

	//Si ya está cargado...
	if (_studioSys->getBank(masterStringPath.c_str(), &bank) == FMOD_OK)
		return;

	FMOD_RESULT res = _studioSys->loadBankFile(masterStringPath.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);

	if (res != FMOD_OK) {
	#ifdef _DEBUG
		std::cerr << "\033[1;31m" << "Couldn´t find '" << masterStringPath << "'" << "\033[0m" << std::endl;
	#endif
		return;
	}

	int numOfStrings;

	bank->getStringCount(&numOfStrings);
	const int maxCharsInFiles = 255;
	char path[maxCharsInFiles];

#ifdef _DEBUG
	std::cout << "Loading all banks included in Master.strings.bank" << std::endl;
#endif

	for (int i = 0; i < numOfStrings; i++) {
		FMOD_GUID info;
		int ret;
		FMOD_RESULT res = bank->getStringInfo(i, &info, path, maxCharsInFiles, &ret);
		if (res != FMOD_OK) continue;

		std::string retrieved = path;
		retrieved.shrink_to_fit();

		if (retrieved.find("Master.string") != std::string::npos) continue;

		if (retrieved.rfind("bank:", 0) == 0) {
			FMOD::Studio::Bank* toLoad;
		#ifdef _DEBUG
			std::cout << "Loading bank at: " << retrieved.substr(5).append(".bank").insert(0, fmodPath) << std::endl;
		#endif
			auto result = _studioSys->loadBankFile(retrieved.substr(5).append(".bank").insert(0, fmodPath).c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &toLoad);
		#ifdef _DEBUG
			if (result != FMOD_OK)
				std::cerr << "\033[1;31m" << "Couldn't find '" << retrieved.substr(5).append(".bank").insert(0, fmodPath) << "'" << "\033[0m" << std::endl;
		#endif
		}
	}
}

FMOD::System* AudioManager::getSystem() const
{
	return _sys;
}

FMOD::Studio::System* LocoMotor::Audio::AudioManager::getStudioSystem() const {
	return _studioSys;
}

FMOD::Sound* AudioManager::getSound(const char* id)
{
	return _soundLib[id] ? _soundLib[id] : nullptr;
}

const char* AudioManager::getError(const unsigned short& errorCode)
{
	return FMOD_ErrorString((FMOD_RESULT)errorCode);
}

AudioManager::AudioManager()
{
	_sys = nullptr;
	_main = nullptr;
	_soundLib = std::unordered_map<std::string, FMOD::Sound*>();
}

AudioManager::~AudioManager()
{
	for (auto& snd : _soundLib) {
		snd.second->release();
	}
	_main->release(); 

	if (_studioSys != nullptr) {
		_studioSys->release();
	}
	else {
		_sys->close();
		_sys->release();
	}
}

bool AudioManager::init(int numChannels, bool useStudio)
{
	if (useStudio) {
		if (!(FMOD::Studio::System::create(&_studioSys) == FMOD_OK)) {
			return false;
		}

		if (!(_studioSys->initialize(numChannels, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0) == FMOD_OK)) {
			_studioSys->release();
			return false;
		}

		if (!(_studioSys->getCoreSystem(&_sys) == FMOD_OK)) {
			_studioSys->release();
			return false;
		}
	}
	else {
		if (!(System_Create(&_sys) == FMOD_OK)) {
			return false;
		}

		if (!(_sys->init(numChannels, FMOD_INIT_NORMAL, 0) == FMOD_OK)) {
			_sys->release();
			return false;
		}
	}

	if (!(_sys->createChannelGroup(0, &_main) == FMOD_OK)) {
		_sys->close();
		_sys->release();
		if (useStudio) {
			_studioSys->release();
		}
		return false;
	}

	_sys->set3DSettings(1.f, 1.f, 1.f);

	return true;
}
