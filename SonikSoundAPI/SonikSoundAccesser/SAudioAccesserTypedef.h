/*
 * SAudioTypedef.h
 *
 *  Created on: 2020/06/07
 *      Author: SONIC
 */

#ifndef SAUDIO_ACCESSER_TYPEDEF_H_
#define SAUDIO_ACCESSER_TYPEDEF_H_

//#include "AudioFormat/AudioLoadTypedef.h"
#include "./AudioSmartPointer.h"

namespace SonikAudio
{
	class SonikAudioInterface;
};

namespace SonikAudio
{
	class SonikAudioPlayer;
};

namespace SonikAudio
{

	typedef SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudio::SonikAudioInterface> SAudioInterface;

	typedef SonikAudioPointer::SonikAudioPlayerSmtPtr<SonikAudio::SonikAudioPlayer> SAudioPlayer;

};


#endif /* SAUDIOTYPEDEF_H_ */