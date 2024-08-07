/*
 * SAudioTypedef.h
 *
 *  Created on: 2020/06/07
 *      Author: SONIC
 */

#ifndef SAUDIO_ACCESSER_TYPEDEF_H_
#define SAUDIO_ACCESSER_TYPEDEF_H_

//#include "AudioFormat/AudioLoadTypedef.h"
#include "../../SmartPointer/SonikSmartPointer.hpp"

namespace SonikAudio
{
	class SonikAudioInterface;
};

namespace SonikAudio
{
	class SonikAudioSEPlayer;
	class SonikAudioBGMPlayer;
};

namespace SonikAudio
{
	class SonikAudioListener;
};


namespace SonikAudio
{

	using SAudioInterface = SonikLib::SharedSmtPtr<SonikAudio::SonikAudioInterface>;

	using SAudioSEPlayer = SonikLib::SharedSmtPtr<SonikAudio::SonikAudioSEPlayer>;
	using SAudioBGMPlayer = SonikLib::SharedSmtPtr<SonikAudio::SonikAudioBGMPlayer>;

	using SAudioListener = SonikLib::SharedSmtPtr<SonikAudio::SonikAudioListener>;

};


#endif /* SAUDIOTYPEDEF_H_ */
