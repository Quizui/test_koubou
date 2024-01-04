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
	class SonikAudioListener;
};

namespace SonikAudio
{

	using SAudioInterface = SonikAudioPointer::SonikAudioInterfaceSmtPtr<SonikAudio::SonikAudioInterface>;

	using SAudioPlayer = SonikAudioPointer::SonikAudioPlayerSmtPtr<SonikAudio::SonikAudioPlayer>;

	using SAudioListener = SonikAudioPointer::SonikAudioNormalSmtPtr<SonikAudio::SonikAudioListener>;

};


#endif /* SAUDIOTYPEDEF_H_ */
