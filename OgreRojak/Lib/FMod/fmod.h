
/* ============================================================================================ */
/* FMOD Ex - Main C/C++ header file. Copyright (c), Firelight Technologies Pty, Ltd. 2004-2006. */
/*                                                                                              */
/* This header is the base header for all other FMOD headers.  If you are programming in C      */
/* use this exclusively, or if you are programming C++ use this in conjunction with FMOD.HPP    */
/*                                                                                              */
/* ============================================================================================ */

#ifndef _FMOD_H
#define _FMOD_H

/*
    FMOD version number.  Check this against FMOD::System::getVersion.
    0xaaaabbcc -> aaaa = major version number.  bb = minor version number.  cc = development version number.
*/

#define FMOD_VERSION    0x00040428

/*
    Compiler specific settings.
*/

#if defined(__CYGWIN32__)
    #define F_CDECL __cdecl
    #define F_STDCALL __stdcall
    #define F_DECLSPEC __declspec
    #define F_DLLEXPORT ( dllexport )
#elif (defined(WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(_XBOX))
    #define F_CDECL _cdecl
    #define F_STDCALL _stdcall
    #define F_DECLSPEC __declspec
    #define F_DLLEXPORT ( dllexport )
#else
    #define F_STDCALL
    #define F_CDECL
    #define F_DECLSPEC
    #define F_DLLEXPORT
    #define __forceinline
#endif

#ifdef DLL_EXPORTS
    #define F_API __declspec(dllexport) F_STDCALL
#else
    #define F_API F_STDCALL
#endif

#define F_CALLBACK F_STDCALL

/*
    FMOD types.
*/

typedef int                      FMOD_BOOL;
typedef struct FMOD_SYSTEM       FMOD_SYSTEM;
typedef struct FMOD_SOUND        FMOD_SOUND;
typedef struct FMOD_CHANNEL      FMOD_CHANNEL;
typedef struct FMOD_CHANNELGROUP FMOD_CHANNELGROUP;
typedef struct FMOD_DSP          FMOD_DSP;
typedef struct FMOD_POLYGON		 FMOD_POLYGON;
typedef struct FMOD_GEOMETRY	 FMOD_GEOMETRY;
typedef struct FMOD_SYNCPOINT	 FMOD_SYNCPOINT;
typedef unsigned int             FMOD_MODE;
typedef unsigned int             FMOD_TIMEUNIT;
typedef unsigned int             FMOD_INITFLAGS;
typedef unsigned int             FMOD_CAPS;

/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a point in 3D space.

    [REMARKS]
    FMOD uses a left handed co-ordinate system by default.
    To use a right handed co-ordinate system specify FMOD_INIT_3D_RIGHTHANDED from FMOD_INITFLAGS in System::init.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    System::set3DListenerAttributes
    System::get3DListenerAttributes
    Channel::set3DAttributes
    Channel::get3DAttributes
    Channel::set3DCustomRolloff
    Channel::get3DCustomRolloff
    Sound::set3DCustomRolloff
    Sound::get3DCustomRolloff
    Geometry::addPolygon
    Geometry::setPolygonVertex
    Geometry::getPolygonVertex
    Geometry::setRotation
    Geometry::getRotation
    Geometry::setPosition
    Geometry::getPosition
    Geometry::setScale
    Geometry::getScale
    FMOD_INITFLAGS
]
*/
typedef struct
{
	float x;        /* X co-ordinate in 3D space. */
    float y;        /* Y co-ordinate in 3D space. */
    float z;        /* Z co-ordinate in 3D space. */
} FMOD_VECTOR;


/*
[ENUM]
[
    [DESCRIPTION]   
    error codes.  Returned from every function.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
]
*/
typedef enum
{
    FMOD_OK,                        /* No errors. */
    FMOD_ERR_ALREADYLOCKED,         /* Tried to call lock a second time before unlock was called. */
    FMOD_ERR_BADCOMMAND,            /* Tried to call a function on a data type that does not allow this type of functionality (ie calling Sound::lock on a streaming sound). */
    FMOD_ERR_CDDA_DRIVERS,          /* Neither NTSCSI nor ASPI could be initialised. */
    FMOD_ERR_CDDA_INIT,             /* An error occurred while initialising the CDDA subsystem. */
    FMOD_ERR_CDDA_INVALID_DEVICE,   /* Couldn't find the specified device. */
    FMOD_ERR_CDDA_NOAUDIO,          /* No audio tracks on the specified disc. */
    FMOD_ERR_CDDA_NODEVICES,        /* No CD/DVD devices were found. */ 
    FMOD_ERR_CDDA_NODISC,           /* No disc present in the specified drive. */
    FMOD_ERR_CDDA_READ,             /* A CDDA read error occurred. */
    FMOD_ERR_CHANNEL_ALLOC,         /* Error trying to allocate a channel. */
    FMOD_ERR_CHANNEL_STOLEN,        /* The specified channel has been reused to play another sound. */
    FMOD_ERR_COM,                   /* A Win32 COM related error occured. COM failed to initialize or a QueryInterface failed meaning a Windows codec or driver was not installed properly. */
    FMOD_ERR_DMA,                   /* DMA Failure.  See debug output for more information. */
    FMOD_ERR_DSP_CONNECTION,        /* DSP connection error.  Connection possibly caused a cyclic dependancy. */
    FMOD_ERR_DSP_FORMAT,            /* DSP Format error.  A DSP unit may have attempted to connect to this network with the wrong format. */
    FMOD_ERR_DSP_NOTFOUND,          /* DSP connection error.  Couldn't find the DSP unit specified. */
    FMOD_ERR_DSP_RUNNING,           /* DSP error.  Cannot perform this operation while the network is in the middle of running.  This will most likely happen if a connection or disconnection is attempted in a DSP callback. */
    FMOD_ERR_DSP_TOOMANYCONNECTIONS,/* DSP connection error.  The unit being connected to or disconnected should only have 1 input or output. */
    FMOD_ERR_FILE_BAD,              /* Error loading file. */
    FMOD_ERR_FILE_COULDNOTSEEK,     /* Couldn't perform seek operation.  This is a limitation of the medium (ie netstreams) or the file format. */
    FMOD_ERR_FILE_EOF,              /* End of file unexpectedly reached while trying to read essential data (truncated data?). */
    FMOD_ERR_FILE_NOTFOUND,         /* File not found. */
    FMOD_ERR_FILE_UNWANTED,         /* Unwanted file access occured. */
    FMOD_ERR_FORMAT,                /* Unsupported file or audio format. */
    FMOD_ERR_HTTP,                  /* A HTTP error occurred. This is a catch-all for HTTP errors not listed elsewhere. */
    FMOD_ERR_HTTP_ACCESS,           /* The specified resource requires authentication or is forbidden. */
    FMOD_ERR_HTTP_PROXY_AUTH,       /* Proxy authentication is required to access the specified resource. */
    FMOD_ERR_HTTP_SERVER_ERROR,     /* A HTTP server error occurred. */
    FMOD_ERR_HTTP_TIMEOUT,          /* The HTTP request timed out. */
    FMOD_ERR_INITIALIZATION,        /* FMOD was not initialized correctly to support this function. */
    FMOD_ERR_INITIALIZED,           /* Cannot call this command after System::init. */
    FMOD_ERR_INTERNAL,              /* An error occured that wasnt supposed to.  Contact support. */
    FMOD_ERR_INVALID_HANDLE,        /* An invalid object handle was used. */
    FMOD_ERR_INVALID_PARAM,         /* An invalid parameter was passed to this function. */
    FMOD_ERR_INVALID_SPEAKER,       /* An invalid speaker was passed to this function based on the current speaker mode. */
    FMOD_ERR_IRX,                   /* PS2 only.  fmodex.irx failed to initialize.  This is most likely because you forgot to load it. */
    FMOD_ERR_MEMORY,                /* Not enough memory or resources. */
    FMOD_ERR_MEMORY_IOP,            /* PS2 only.  Not enough memory or resources on PlayStation 2 IOP ram. */
    FMOD_ERR_MEMORY_SRAM,           /* Not enough memory or resources on console sound ram. */
    FMOD_ERR_NEEDS2D,               /* Tried to call a command on a 3d sound when the command was meant for 2d sound. */
    FMOD_ERR_NEEDS3D,               /* Tried to call a command on a 2d sound when the command was meant for 3d sound. */
    FMOD_ERR_NEEDSHARDWARE,         /* Tried to use a feature that requires hardware support.  (ie trying to play a VAG compressed sound in software on PS2). */
    FMOD_ERR_NEEDSSOFTWARE,         /* Tried to use a feature that requires the software engine.  Software engine has either been turned off, or command was executed on a hardware channel which does not support this feature. */
    FMOD_ERR_NET_CONNECT,           /* Couldn't connect to the specified host. */
    FMOD_ERR_NET_SOCKET_ERROR,      /* A socket error occurred.  This is a catch-all for socket-related errors not listed elsewhere. */
    FMOD_ERR_NET_URL,               /* The specified URL couldn't be resolved. */
    FMOD_ERR_NOTREADY,              /* Operation could not be performed because specified sound is not ready. */
    FMOD_ERR_OUTPUT_ALLOCATED,      /* Error initializing output device, but more specifically, the output device is already in use and cannot be reused. */
    FMOD_ERR_OUTPUT_CREATEBUFFER,   /* Error creating hardware sound buffer. */
    FMOD_ERR_OUTPUT_DRIVERCALL,     /* A call to a standard soundcard driver failed, which could possibly mean a bug in the driver or resources were missing or exhausted. */
    FMOD_ERR_OUTPUT_FORMAT,         /* Soundcard does not support the minimum features needed for this soundsystem (16bit stereo output). */
    FMOD_ERR_OUTPUT_INIT,           /* Error initializing output device. */
    FMOD_ERR_OUTPUT_NOHARDWARE,     /* FMOD_HARDWARE was specified but the sound card does not have the resources nescessary to play it. */
    FMOD_ERR_OUTPUT_NOSOFTWARE,     /* Attempted to create a software sound but no software channels were specified in System::init. */
    FMOD_ERR_PAN,                   /* Panning only works with mono or stereo sound sources. */
    FMOD_ERR_PLUGIN,                /* An unspecified error has been returned from a 3rd party plugin. */
    FMOD_ERR_PLUGIN_MISSING,        /* A requested output, dsp unit type or codec was not available. */
    FMOD_ERR_PLUGIN_RESOURCE,       /* A resource that the plugin requires cannot be found. (ie the DLS file for MIDI playback) */
    FMOD_ERR_RECORD,                /* An error occured trying to initialize the recording device. */
    FMOD_ERR_REVERB_INSTANCE,       /* Specified Instance in FMOD_REVERB_PROPERTIES couldn't be set. Most likely because another application has locked the EAX4 FX slot. */
    FMOD_ERR_SUBSOUNDS,             /* The error occured because the sound referenced contains subsounds.  (ie you cannot play the parent sound as a static sample, only its subsounds.) */
    FMOD_ERR_SUBSOUND_ALLOCATED,    /* This subsound is already being used by another sound, you cannot have more than one parent to a sound.  Null out the other parent's entry first. */
    FMOD_ERR_TAGNOTFOUND,           /* The specified tag could not be found or there are no tags. */
    FMOD_ERR_TOOMANYCHANNELS,       /* The sound created exceeds the allowable input channel count.  This can be increased with System::setMaxInputChannels. */
    FMOD_ERR_UNIMPLEMENTED,         /* Something in FMOD hasn't been implemented when it should be! contact support! */
    FMOD_ERR_UNINITIALIZED,         /* This command failed because System::init or System::setDriver was not called. */
    FMOD_ERR_UNSUPPORTED,           /* A command issued was not supported by this object.  Possibly a plugin without certain callbacks specified. */
    FMOD_ERR_UPDATE,                /* An error caused by System::update occured. */
    FMOD_ERR_VERSION,               /* The version number of this file format is not supported. */

    FMOD_RESULT_FORCEINT = 65536    /* Makes sure this enum is signed 32bit. */
} FMOD_RESULT;


/*
[ENUM]
[
    [DESCRIPTION]   
    These output types are used with System::setOutput/System::getOutput, to choose which output method to use.
  
    [REMARKS]
    To pass information to the driver when initializing fmod use the extradriverdata parameter in System::init for the following reasons.
    - FMOD_OUTPUTTYPE_WAVWRITER - extradriverdata is a pointer to a char * filename that the wav writer will output to.
    - FMOD_OUTPUTTYPE_WAVWRITER_NRT - extradriverdata is a pointer to a char * filename that the wav writer will output to.
    - FMOD_OUTPUTTYPE_DSOUND - extradriverdata is a pointer to a HWND so that FMOD can set the focus on the audio for a particular window.
    - FMOD_OUTPUTTYPE_GC - extradriverdata is a pointer to a FMOD_GC_INFO struct. This can be found in fmodgc.h.
    - FMOD_OUTPUTTYPE_ALSA - extradriverdata is a pointer to a char * argument if required by the chosen ALSA driver. 
    Currently these are the only FMOD drivers that take extra information.  Other unknown plugins may have different requirements.
    
    - FMOD_OUTPUTTYPE_OPENAL - this requires version 1.1 or greater. An implementation of this is available at http://www.openal.org/downloads.html
    
    Note! If FMOD_OUTPUTTYPE_WAVWRITER_NRT or FMOD_OUTPUTTYPE_NOSOUND_NRT are used, and if the System::update function is being called
    very quickly (ie for a non realtime decode) it may be being called too quickly for the FMOD streamer thread to respond to.  
    The result will be a skipping/stuttering output in the captured audio.
    To remedy this, disable the FMOD Ex streamer thread, and use FMOD_INIT_STREAM_FROM_UPDATE can be used to avoid skipping in 
    the output stream, as it will lock the mixer and the streamer together in the same thread.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    System::setOutput
    System::getOutput
    System::setSoftwareFormat
    System::getSoftwareFormat
    System::init
    System::update
    FMOD_INITFLAGS
]
*/
typedef enum
{
    FMOD_OUTPUTTYPE_AUTODETECT,      /* Picks the best output mode for the platform.  This is the default. */
                                     
    FMOD_OUTPUTTYPE_UNKNOWN,         /* All         - 3rd party plugin, unknown.  This is for use with System::getOutput only. */
    FMOD_OUTPUTTYPE_NOSOUND,         /* All         - All calls in this mode succeed but make no sound. */
    FMOD_OUTPUTTYPE_WAVWRITER,       /* All         - Writes output to fmodoutput.wav by default.  Use the 'extradriverdata' parameter in System::init, by simply passing the filename as a string, to set the wav filename. */
    FMOD_OUTPUTTYPE_NOSOUND_NRT,     /* All         - Non-realtime version of FMOD_OUTPUTTYPE_NOSOUND.  User can drive mixer with System::update at whatever rate they want. */
    FMOD_OUTPUTTYPE_WAVWRITER_NRT,   /* All         - Non-realtime version of FMOD_OUTPUTTYPE_WAVWRITER.  User can drive mixer with System::update at whatever rate they want. */
                                     
    FMOD_OUTPUTTYPE_DSOUND,          /* Win32/Win64 - DirectSound output.  Use this to get hardware accelerated 3d audio and EAX Reverb support. (Default on Windows) */
    FMOD_OUTPUTTYPE_WINMM,           /* Win32/Win64 - Windows Multimedia output. */
    FMOD_OUTPUTTYPE_ASIO,            /* Win32       - Low latency ASIO driver. */
    FMOD_OUTPUTTYPE_OSS,             /* Linux       - Open Sound System output. (Default on Linux) */
    FMOD_OUTPUTTYPE_ALSA,            /* Linux       - Advanced Linux Sound Architecture output. */
    FMOD_OUTPUTTYPE_ESD,             /* Linux       - Enlightment Sound Daemon output. */
    FMOD_OUTPUTTYPE_SOUNDMANAGER,    /* Mac         - Macintosh SoundManager output.  (Default on Mac carbon library)*/
    FMOD_OUTPUTTYPE_COREAUDIO,       /* Mac         - Macintosh CoreAudio output.  (Default on Mac OSX library) */
    FMOD_OUTPUTTYPE_XBOX,            /* Xbox        - Native hardware output. (Default on Xbox) */
    FMOD_OUTPUTTYPE_PS2,             /* PS2         - Native hardware output. (Default on PS2) */
    FMOD_OUTPUTTYPE_PS3,             /* PS3         - Native hardware output. (Default on PS3) */
    FMOD_OUTPUTTYPE_GC,              /* GameCube    - Native hardware output. (Default on GameCube) */
    FMOD_OUTPUTTYPE_XBOX360,         /* Xbox 360    - Native hardware output. (Default on Xbox 360) */
    FMOD_OUTPUTTYPE_PSP,             /* PSP         - Native hardware output. (Default on PSP) */
    FMOD_OUTPUTTYPE_OPENAL,          /* Win32/Win64 - OpenAL 1.1 output. Use this for lower CPU overhead than FMOD_OUTPUTTYPE_DSOUND, and also Vista H/W support with Creative Labs cards. */
	FMOD_OUTPUTTYPE_WII,			 /* Wii			- Native hardware output. (Default on Wii) */

    FMOD_OUTPUTTYPE_MAX,             /* Maximum number of output types supported. */
    FMOD_OUTPUTTYPE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_OUTPUTTYPE;


/*
[DEFINE] 
[
    [NAME]
    FMOD_CAPS

    [DESCRIPTION]   
    Bit fields to use with System::getDriverCaps to determine the capabilities of a card / output device.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::getDriverCaps
]
*/
#define FMOD_CAPS_NONE                   0x00000000  /* Device has no special capabilities. */
#define FMOD_CAPS_HARDWARE               0x00000001  /* Device supports hardware mixing. */
#define FMOD_CAPS_HARDWARE_EMULATED      0x00000002  /* Device supports FMOD_HARDWARE but it will be mixed on the CPU by the kernel (not FMOD's software mixer). */
#define FMOD_CAPS_OUTPUT_MULTICHANNEL    0x00000004  /* Device can do multichannel output, ie greater than 2 channels. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCM8     0x00000008  /* Device can output to 8bit integer PCM. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCM16    0x00000010  /* Device can output to 16bit integer PCM. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCM24    0x00000020  /* Device can output to 24bit integer PCM. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCM32    0x00000040  /* Device can output to 32bit integer PCM. */
#define FMOD_CAPS_OUTPUT_FORMAT_PCMFLOAT 0x00000080  /* Device can output to 32bit floating point PCM. */
#define FMOD_CAPS_REVERB_EAX2            0x00000100  /* Device supports EAX2 reverb. */
#define FMOD_CAPS_REVERB_EAX3            0x00000200  /* Device supports EAX3 reverb. */
#define FMOD_CAPS_REVERB_EAX4            0x00000400  /* Device supports EAX4 reverb  */
#define FMOD_CAPS_REVERB_I3DL2           0x00000800  /* Device supports I3DL2 reverb. */
#define FMOD_CAPS_REVERB_LIMITED         0x00001000  /* Device supports some form of limited hardware reverb, maybe parameterless and only selectable by environment. */
/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]   
    These are speaker types defined for use with the System::setSpeakerMode or System::getSpeakerMode command.

    [REMARKS]
    These are important notes on speaker modes in regards to sounds created with FMOD_SOFTWARE.
    Note below the phrase 'sound channels' is used.  These are the subchannels inside a sound, they are not related and 
    have nothing to do with the FMOD class "Channel".
    For example a mono sound has 1 sound channel, a stereo sound has 2 sound channels, and an AC3 or 6 channel wav file have 6 "sound channels".
    
    FMOD_SPEAKERMODE_RAW
    ---------------------
    This mode is for output devices that are not specifically mono/stereo/quad/surround/5.1 or 7.1, but are multichannel.
    Use System::setSoftwareFormat to specify the number of speakers you want to address, otherwise it will default to 2 (stereo).
    Sound channels map to speakers sequentially, so a mono sound maps to output speaker 0, stereo sound maps to output speaker 0 & 1.
    The user assumes knowledge of the speaker order.  FMOD_SPEAKER enumerations may not apply, so raw channel indices should be used.
    Multichannel sounds map input channels to output channels 1:1. 
    Channel::setPan and Channel::setSpeakerMix do not work.
    Speaker levels must be manually set with Channel::setSpeakerLevels.
    
    FMOD_SPEAKERMODE_MONO
    ---------------------
    This mode is for a 1 speaker arrangement.
    Panning does not work in this speaker mode.
    Mono, stereo and multichannel sounds have each sound channel played on the one speaker unity.
    Mix behaviour for multichannel sounds can be set with Channel::setSpeakerLevels.
    Channel::setSpeakerMix does not work.
    
    FMOD_SPEAKERMODE_STEREO
    -----------------------
    This mode is for 2 speaker arrangements that have a left and right speaker.
    - Mono sounds default to an even distribution between left and right.  They can be panned with Channel::setPan.
    - Stereo sounds default to the middle, or full left in the left speaker and full right in the right speaker.  
    - They can be cross faded with Channel::setPan.
    - Multichannel sounds have each sound channel played on each speaker at unity.
    - Mix behaviour for multichannel sounds can be set with Channel::setSpeakerLevels.
    - Channel::setSpeakerMix works but only front left and right parameters are used, the rest are ignored.
    
    FMOD_SPEAKERMODE_QUAD
    ------------------------
    This mode is for 4 speaker arrangements that have a front left, front right, rear left and a rear right speaker.
    - Mono sounds default to an even distribution between front left and front right.  They can be panned with Channel::setPan.
    - Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.
    - They can be cross faded with Channel::setPan.
    - Multichannel sounds default to all of their sound channels being played on each speaker in order of input.
    - Mix behaviour for multichannel sounds can be set with Channel::setSpeakerLevels.
    - Channel::setSpeakerMix works but side left, side right, center and lfe are ignored.
    
    FMOD_SPEAKERMODE_SURROUND
    ------------------------
    This mode is for 4 speaker arrangements that have a front left, front right, front center and a rear center.
    - Mono sounds default to the center speaker.  They can be panned with Channel::setPan.
    - Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.  
    - They can be cross faded with Channel::setPan.
    - Multichannel sounds default to all of their sound channels being played on each speaker in order of input.
    - Mix behaviour for multichannel sounds can be set with Channel::setSpeakerLevels.
    - Channel::setSpeakerMix works but side left, side right and lfe are ignored, and rear left / rear right are averaged into the rear speaker.
    
    FMOD_SPEAKERMODE_5POINT1
    ------------------------
    This mode is for 5.1 speaker arrangements that have a left/right/center/rear left/rear right and a subwoofer speaker.
    - Mono sounds default to the center speaker.  They can be panned with Channel::setPan.
    - Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.  
    - They can be cross faded with Channel::setPan.
    - Multichannel sounds default to all of their sound channels being played on each speaker in order of input.  
    - Mix behaviour for multichannel sounds can be set with Channel::setSpeakerLevels.
    - Channel::setSpeakerMix works but side left / side right are ignored.
    
    FMOD_SPEAKERMODE_7POINT1
    ------------------------
    This mode is for 7.1 speaker arrangements that have a left/right/center/rear left/rear right/side left/side right 
    and a subwoofer speaker.
    - Mono sounds default to the center speaker.  They can be panned with Channel::setPan.
    - Stereo sounds default to the left sound channel played on the front left, and the right sound channel played on the front right.  
    - They can be cross faded with Channel::setPan.
    - Multichannel sounds default to all of their sound channels being played on each speaker in order of input.  
    - Mix behaviour for multichannel sounds can be set with Channel::setSpeakerLevels.
    - Channel::setSpeakerMix works and every parameter is used to set the balance of a sound in any speaker.
    
    FMOD_SPEAKERMODE_PROLOGIC
    ------------------------------------------------------
    This mode is for mono, stereo, 5.1 and 7.1 speaker arrangements, as it is backwards and forwards compatible with stereo, 
    but to get a surround effect a Dolby Prologic or Prologic 2 hardware decoder / amplifier is needed.
    Pan behaviour is the same as FMOD_SPEAKERMODE_5POINT1.
    
    If this function is called the numoutputchannels setting in System::setSoftwareFormat is overwritten.
    
    For 3D sounds, panning is determined at runtime by the 3D subsystem based on the speaker mode to determine which speaker the 
    sound should be placed in.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::setSpeakerMode
    System::getSpeakerMode
    System::getDriverCaps
    System::setSoftwareFormat
    Channel::setSpeakerLevels
]
*/
typedef enum
{
    FMOD_SPEAKERMODE_RAW,              /* There is no specific speakermode.  Sound channels are mapped in order of input to output.  Use System::setSoftwareFormat to specify speaker count. See remarks for more information. */
    FMOD_SPEAKERMODE_MONO,             /* The speakers are monaural. */
    FMOD_SPEAKERMODE_STEREO,           /* The speakers are stereo (DEFAULT). */
    FMOD_SPEAKERMODE_QUAD,             /* 4 speaker setup.  This includes front left, front right, rear left, rear right.  */
    FMOD_SPEAKERMODE_SURROUND,         /* 4 speaker setup.  This includes front left, front right, center, rear center (rear left/rear right are averaged). */
    FMOD_SPEAKERMODE_5POINT1,          /* 5.1 speaker setup.  This includes front left, front right, center, rear left, rear right and a subwoofer. */
    FMOD_SPEAKERMODE_7POINT1,          /* 7.1 speaker setup.  This includes front left, front right, center, rear left, rear right, side left, side right and a subwoofer. */
    FMOD_SPEAKERMODE_PROLOGIC,         /* Stereo output, but data is encoded in a way that is picked up by a Prologic/Prologic2 decoder and split into a 5.1 speaker setup. */

    FMOD_SPEAKERMODE_MAX,              /* Maximum number of speaker modes supported. */
    FMOD_SPEAKERMODE_FORCEINT = 65536  /* Makes sure this enum is signed 32bit. */
} FMOD_SPEAKERMODE;


/*
[ENUM]
[
    [DESCRIPTION]   
    These are speaker types defined for use with the Channel::setSpeakerLevels command.
    It can also be used for speaker placement in the System::setSpeakerPosition command.

    [REMARKS]
    If you are using FMOD_SPEAKERMODE_RAW and speaker assignments are meaningless, just cast a raw integer value to this type.
    For example (FMOD_SPEAKER)7 would use the 7th speaker (also the same as FMOD_SPEAKER_SIDE_RIGHT).
    Values higher than this can be used if an output system has more than 8 speaker types / output channels.  15 is the current maximum.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    FMOD_SPEAKERMODE
    Channel::setSpeakerLevels
    Channel::getSpeakerLevels
    System::setSpeakerPosition
    System::getSpeakerPosition
]
*/
typedef enum
{
    FMOD_SPEAKER_FRONT_LEFT,
    FMOD_SPEAKER_FRONT_RIGHT,
    FMOD_SPEAKER_FRONT_CENTER,
    FMOD_SPEAKER_LOW_FREQUENCY,
    FMOD_SPEAKER_BACK_LEFT,
    FMOD_SPEAKER_BACK_RIGHT,
    FMOD_SPEAKER_SIDE_LEFT,
    FMOD_SPEAKER_SIDE_RIGHT,
    
    FMOD_SPEAKER_MAX,                                       /* Maximum number of speaker types supported. */
    FMOD_SPEAKER_MONO        = FMOD_SPEAKER_FRONT_LEFT,     /* For use with FMOD_SPEAKERMODE_MONO and Channel::SetSpeakerLevels.  Mapped to same value as FMOD_SPEAKER_FRONT_LEFT. */
    FMOD_SPEAKER_BACK_CENTER = FMOD_SPEAKER_LOW_FREQUENCY,  /* For use with FMOD_SPEAKERMODE_SURROUND and Channel::SetSpeakerLevels only.  Mapped to same value as FMOD_SPEAKER_LOW_FREQUENCY. */
    FMOD_SPEAKER_FORCEINT    = 65536                        /* Makes sure this enum is signed 32bit. */
} FMOD_SPEAKER;


/*
[ENUM]
[
    [DESCRIPTION]   
    These are plugin types defined for use with the System::getNumPlugins, 
    System::getPluginInfo and System::unloadPlugin functions.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::getNumPlugins
    System::getPluginInfo
    System::unloadPlugin
]
*/
typedef enum
{
    FMOD_PLUGINTYPE_OUTPUT,          /* The plugin type is an output module.  FMOD mixed audio will play through one of these devices */
    FMOD_PLUGINTYPE_CODEC,           /* The plugin type is a file format codec.  FMOD will use these codecs to load file formats for playback. */
    FMOD_PLUGINTYPE_DSP,             /* The plugin type is a DSP unit.  FMOD will use these plugins as part of its DSP network to apply effects to output or generate sound in realtime. */

    FMOD_PLUGINTYPE_MAX,             /* Maximum number of plugin types supported. */
    FMOD_PLUGINTYPE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_PLUGINTYPE;


/*
[DEFINE]
[
    [NAME]
    FMOD_INITFLAGS

    [DESCRIPTION]   
    Initialization flags.  Use them with System::init in the flags parameter to change various behaviour.  

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::init
    System::update 
]
*/
#define FMOD_INIT_NORMAL                  0x00000000 /* All platforms - Initialize normally */
#define FMOD_INIT_STREAM_FROM_UPDATE      0x00000001 /* All platforms - No stream thread is created internally.  Streams are driven from System::update.  Mainly used with non-realtime outputs. */
#define FMOD_INIT_3D_RIGHTHANDED          0x00000002 /* All platforms - FMOD will treat +X as left, +Y as up and +Z as forwards. */
#define FMOD_INIT_DISABLESOFTWARE         0x00000004 /* All platforms - Disable software mixer to save memory.  Anything created with FMOD_SOFTWARE will fail and DSP will not work. */
#define FMOD_INIT_DSOUND_HRTFNONE         0x00000200 /* Win32 only - for DirectSound output - FMOD_HARDWARE | FMOD_3D buffers use simple stereo panning/doppler/attenuation when 3D hardware acceleration is not present. */
#define FMOD_INIT_DSOUND_HRTFLIGHT        0x00000400 /* Win32 only - for DirectSound output - FMOD_HARDWARE | FMOD_3D buffers use a slightly higher quality algorithm when 3D hardware acceleration is not present. */
#define FMOD_INIT_DSOUND_HRTFFULL         0x00000800 /* Win32 only - for DirectSound output - FMOD_HARDWARE | FMOD_3D buffers use full quality 3D playback when 3d hardware acceleration is not present. */
#define FMOD_INIT_PS2_DISABLECORE0REVERB  0x00010000 /* PS2 only - Disable reverb on CORE 0 to regain 256k SRAM. */
#define FMOD_INIT_PS2_DISABLECORE1REVERB  0x00020000 /* PS2 only - Disable reverb on CORE 1 to regain 256k SRAM. */
#define FMOD_INIT_PS2_DONTUSESCRATCHPAD   0x00040000 /* PS2 only - Disable FMOD's usage of the scratchpad. */
#define FMOD_INIT_XBOX_REMOVEHEADROOM     0x00100000 /* Xbox only - By default DirectSound attenuates all sound by 6db to avoid clipping/distortion.  CAUTION.  If you use this flag you are responsible for the final mix to make sure clipping / distortion doesn't happen. */
/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]   
    These definitions describe the type of song being played.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    Sound::getFormat
]
*/
typedef enum
{
    FMOD_SOUND_TYPE_UNKNOWN,         /* 3rd party / unknown plugin format. */
    FMOD_SOUND_TYPE_AAC,             /* AAC. */
    FMOD_SOUND_TYPE_AIFF,            /* AIFF. */
    FMOD_SOUND_TYPE_ASF,             /* Microsoft Advanced Systems Format (ie WMA/ASF/WMV). */
    FMOD_SOUND_TYPE_AT3,             /* Sony ATRAC 3 format */
    FMOD_SOUND_TYPE_CDDA,            /* Digital CD audio. */
    FMOD_SOUND_TYPE_DLS,             /* Sound font / downloadable sound bank. */
    FMOD_SOUND_TYPE_FLAC,            /* FLAC lossless codec. */
    FMOD_SOUND_TYPE_FSB,             /* FMOD Sample Bank. */
    FMOD_SOUND_TYPE_GCADPCM,         /* GameCube ADPCM */
    FMOD_SOUND_TYPE_IT,              /* Impulse Tracker. */
    FMOD_SOUND_TYPE_MIDI,            /* MIDI. */
    FMOD_SOUND_TYPE_MOD,             /* Protracker / Fasttracker MOD. */
    FMOD_SOUND_TYPE_MPEG,            /* MP2/MP3 MPEG. */
    FMOD_SOUND_TYPE_OGGVORBIS,       /* Ogg vorbis. */
    FMOD_SOUND_TYPE_PLAYLIST,        /* Information only from ASX/PLS/M3U/WAX playlists */
    FMOD_SOUND_TYPE_RAW,             /* Raw PCM data. */
    FMOD_SOUND_TYPE_S3M,             /* ScreamTracker 3. */
    FMOD_SOUND_TYPE_SF2,             /* Sound font 2 format. */
    FMOD_SOUND_TYPE_USER,            /* User created sound. */
    FMOD_SOUND_TYPE_WAV,             /* Microsoft WAV. */
    FMOD_SOUND_TYPE_XM,              /* FastTracker 2 XM. */
    FMOD_SOUND_TYPE_XMA,             /* Xbox360 XMA */
    FMOD_SOUND_TYPE_VAG,             /* PlayStation 2 / PlayStation Portable adpcm VAG format. */

    FMOD_SOUND_TYPE_MAX,             /* Maximum number of sound types supported. */
    FMOD_SOUND_TYPE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_SOUND_TYPE;


/*
[ENUM]
[
    [DESCRIPTION]   
    These definitions describe the native format of the hardware or software buffer that will be used.

    [REMARKS]
    This is the format the native hardware or software buffer will be or is created in.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::createSound
    Sound::getFormat
]
*/
typedef enum
{
    FMOD_SOUND_FORMAT_NONE,             /* Unitialized / unknown. */
    FMOD_SOUND_FORMAT_PCM8,             /* 8bit integer PCM data. */
    FMOD_SOUND_FORMAT_PCM16,            /* 16bit integer PCM data.  */
    FMOD_SOUND_FORMAT_PCM24,            /* 24bit integer PCM data.  */
    FMOD_SOUND_FORMAT_PCM32,            /* 32bit integer PCM data.  */
    FMOD_SOUND_FORMAT_PCMFLOAT,         /* 32bit floating point PCM data.  */
    FMOD_SOUND_FORMAT_GCADPCM,          /* Compressed GameCube DSP data. */
    FMOD_SOUND_FORMAT_IMAADPCM,         /* Compressed IMA ADPCM / Xbox ADPCM data. */
    FMOD_SOUND_FORMAT_VAG,              /* Compressed PlayStation 2 / PlayStation Portable ADPCM data. */
    FMOD_SOUND_FORMAT_XMA,              /* Compressed Xbox360 data. */
    FMOD_SOUND_FORMAT_MPEG,             /* Compressed MPEG layer 2 or 3 data. */

    FMOD_SOUND_FORMAT_MAX,              /* Maximum number of sound formats supported. */   
    FMOD_SOUND_FORMAT_FORCEINT = 65536  /* Makes sure this enum is signed 32bit. */
} FMOD_SOUND_FORMAT;


/*
[DEFINE]
[
    [NAME] 
    FMOD_MODE

    [DESCRIPTION]   
    Sound description bitfields, bitwise OR them together for loading and describing sounds.

    [REMARKS]
    By default a sound will open as a static sound that is decompressed fully into memory.
    To have a sound stream instead, use FMOD_CREATESTREAM.
    Some opening modes (ie FMOD_OPENUSER, FMOD_OPENMEMORY, FMOD_OPENRAW) will need extra information.
    This can be provided using the FMOD_CREATESOUNDEXINFO structure.
    
    On Playstation 2, non VAG formats will default to FMOD_SOFTWARE if FMOD_HARDWARE is not specified.
    This is due to PS2 hardware not supporting PCM data.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::createSound
    System::createStream
    Sound::setMode
    Sound::getMode
    Channel::setMode
    Channel::getMode
    Sound::set3DCustomRolloff
    Channel::set3DCustomRolloff
    Sound::getOpenState
]
*/
#define FMOD_DEFAULT                0x00000000  /* FMOD_DEFAULT is a default sound type.  Equivalent to all the defaults listed below.  FMOD_LOOP_OFF, FMOD_2D, FMOD_HARDWARE. */
#define FMOD_LOOP_OFF               0x00000001  /* For non looping sounds. (DEFAULT).  Overrides FMOD_LOOP_NORMAL / FMOD_LOOP_BIDI. */
#define FMOD_LOOP_NORMAL            0x00000002  /* For forward looping sounds. */
#define FMOD_LOOP_BIDI              0x00000004  /* For bidirectional looping sounds. (only works on software mixed static sounds). */
#define FMOD_2D                     0x00000008  /* Ignores any 3d processing. (DEFAULT). */
#define FMOD_3D                     0x00000010  /* Makes the sound positionable in 3D.  Overrides FMOD_2D. */
#define FMOD_HARDWARE               0x00000020  /* Attempts to make sounds use hardware acceleration. (DEFAULT). */
#define FMOD_SOFTWARE               0x00000040  /* Makes the sound be mixed by the FMOD CPU based software mixer.  Overrides FMOD_HARDWARE.  Use this for FFT, DSP, compressed sample support, 2D multi-speaker support and other software related features. */
#define FMOD_CREATESTREAM           0x00000080  /* Decompress at runtime, streaming from the source provided (ie from disk).  Overrides FMOD_CREATESAMPLE and FMOD_CREATECOMPRESSEDSAMPLE.  Note a stream can only be played once at a time due to a stream only having 1 stream buffer and file handle.  Open multiple streams to have them play concurrently. */
#define FMOD_CREATESAMPLE           0x00000100  /* Decompress at loadtime, decompressing or decoding whole file into memory as the target sample format (ie PCM).  Fastest for playback and most flexible.  */
#define FMOD_CREATECOMPRESSEDSAMPLE 0x00000200  /* Load MP2, MP3, IMAADPCM or XMA into memory and leave it compressed.  During playback the FMOD software mixer will decode it in realtime as a 'compressed sample'.  Can only be used in combination with FMOD_SOFTWARE.  Overrides FMOD_CREATESAMPLE.  If the sound data is not ADPCM, MPEG or XMA it will behave as if it was created with FMOD_CREATESAMPLE and decode the sound into PCM. */
#define FMOD_OPENUSER               0x00000400  /* Opens a user created static sample or stream. Use FMOD_CREATESOUNDEXINFO to specify format and/or read callbacks.  If a user created 'sample' is created with no read callback, the sample will be empty.  Use Sound::lock and Sound::unlock to place sound data into the sound if this is the case. */
#define FMOD_OPENMEMORY             0x00000800  /* "name_or_data" will be interpreted as a pointer to memory instead of filename for creating sounds.  Use FMOD_CREATESOUNDEXINFO to specify length. */
#define FMOD_OPENRAW                0x00001000  /* Will ignore file format and treat as raw pcm.  Use FMOD_CREATESOUNDEXINFO to specify format.  Requires at least defaultfrequency, numchannels and format to be specified before it will open. */
#define FMOD_OPENONLY               0x00002000  /* Just open the file, dont prebuffer or read.  Good for fast opens for info, or when sound::readData is to be used. */
#define FMOD_ACCURATETIME           0x00004000  /* For System::createSound - for accurate Sound::getLength/Channel::setPosition on VBR MP3, AAC and MOD/S3M/XM/IT/MIDI files.  Scans file first, so takes longer to open. FMOD_OPENONLY does not affect this. */
#define FMOD_MPEGSEARCH             0x00008000  /* For corrupted / bad MP3 files.  This will search all the way through the file until it hits a valid MPEG header.  Normally only searches for 4k. */
#define FMOD_NONBLOCKING            0x00010000  /* For opening sounds asyncronously.  Use Sound::getOpenState to poll the state of the sound as it opens in the background. */
#define FMOD_UNIQUE                 0x00020000  /* Unique sound, can only be played one at a time */
#define FMOD_3D_HEADRELATIVE        0x00040000  /* Make the sound's position, velocity and orientation relative to the listener. */
#define FMOD_3D_WORLDRELATIVE       0x00080000  /* Make the sound's position, velocity and orientation absolute (relative to the world). (DEFAULT) */
#define FMOD_3D_LOGROLLOFF          0x00100000  /* This sound will follow the standard logarithmic rolloff model where mindistance = full volume, maxdistance = where sound stops attenuating, and rolloff is fixed according to the global rolloff factor.  (DEFAULT) */
#define FMOD_3D_LINEARROLLOFF       0x00200000  /* This sound will follow a linear rolloff model where mindistance = full volume, maxdistance = silence.  Rolloffscale is ignored. */
#define FMOD_3D_CUSTOMROLLOFF       0x04000000  /* This sound will follow a rolloff model defined by Sound::set3DCustomRolloff / Channel::set3DCustomRolloff.  */
#define FMOD_CDDA_FORCEASPI         0x00400000  /* For CDDA sounds only - use ASPI instead of NTSCSI to access the specified CD/DVD device. */
#define FMOD_CDDA_JITTERCORRECT     0x00800000  /* For CDDA sounds only - perform jitter correction. Jitter correction helps produce a more accurate CDDA stream at the cost of more CPU time. */
#define FMOD_UNICODE                0x01000000  /* Filename is double-byte unicode. */
#define FMOD_IGNORETAGS             0x02000000  /* Skips id3v2/asf/etc tag checks when opening a sound, to reduce seek/read overhead when opening files (helps with CD performance). */
#define FMOD_LOWMEM                 0x08000000  /* Removes some features from samples to give a lower memory overhead, like Sound::getName. */
/* [DEFINE_END] */


/*
[ENUM]
[
    [DESCRIPTION]   
    These values describe what state a sound is in after FMOD_NONBLOCKING has been used to open it.

    [REMARKS]    

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    Sound::getOpenState
    FMOD_MODE
]
*/
typedef enum
{
    FMOD_OPENSTATE_READY = 0,       /* Opened and ready to play. */
    FMOD_OPENSTATE_LOADING,         /* Initial load in progress. */
    FMOD_OPENSTATE_ERROR,           /* Failed to open - file not found, out of memory etc.  See return value of Sound::getOpenState for what happened. */
    FMOD_OPENSTATE_CONNECTING,      /* Connecting to remote host (internet sounds only). */
    FMOD_OPENSTATE_BUFFERING,       /* Buffering data. */
    FMOD_OPENSTATE_SEEKING,         /* Seeking to subsound and re-flushing stream buffer. */

    FMOD_OPENSTATE_MAX,             /* Maximum number of open state types. */
    FMOD_OPENSTATE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_OPENSTATE;


/*
[ENUM]
[
    [DESCRIPTION]   
    These callback types are used with Channel::setCallback.

    [REMARKS]
    Each callback has commanddata parameters passed int unique to the type of callback.
    See reference to FMOD_CHANNEL_CALLBACK to determine what they might mean for each type of callback.
    
    <b>Note!</b>  Currently the user must call System::update for these callbacks to trigger!

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    Channel::setCallback
    FMOD_CHANNEL_CALLBACK
    System::update
]
*/
typedef enum
{
    FMOD_CHANNEL_CALLBACKTYPE_END,                  /* Called when a sound ends. */
    FMOD_CHANNEL_CALLBACKTYPE_VIRTUALVOICE,         /* Called when a voice is swapped out or swapped in. */
    FMOD_CHANNEL_CALLBACKTYPE_SYNCPOINT,            /* Called when a syncpoint is encountered.  Can be from wav file markers. */

    FMOD_CHANNEL_CALLBACKTYPE_MAX,                  /* Maximum number of callback types supported. */
    FMOD_CHANNEL_CALLBACKTYPE_FORCEINT = 65536      /* Makes sure this enum is signed 32bit. */
} FMOD_CHANNEL_CALLBACKTYPE;


/*
[ENUM]
[
    [DESCRIPTION]   
    List of windowing methods used in spectrum analysis to reduce leakage / transient signals intefering with the analysis.
    This is a problem with analysis of continuous signals that only have a small portion of the signal sample (the fft window size).
    Windowing the signal with a curve or triangle tapers the sides of the fft window to help alleviate this problem.

    [REMARKS]
    Cyclic signals such as a sine wave that repeat their cycle in a multiple of the window size do not need windowing.
    I.e. If the sine wave repeats every 1024, 512, 256 etc samples and the FMOD fft window is 1024, then the signal would not need windowing.
    Not windowing is the same as FMOD_DSP_FFT_WINDOW_RECT, which is the default.
    If the cycle of the signal (ie the sine wave) is not a multiple of the window size, it will cause frequency abnormalities, so a different windowing method is needed.
    
    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    System::getSpectrum
    Channel::getSpectrum
]
*/
typedef enum
{
    FMOD_DSP_FFT_WINDOW_RECT,            /* w[n] = 1.0                                                                                            */
    FMOD_DSP_FFT_WINDOW_TRIANGLE,        /* w[n] = TRI(2n/N)                                                                                      */
    FMOD_DSP_FFT_WINDOW_HAMMING,         /* w[n] = 0.54 - (0.46 * COS(n/N) )                                                                      */
    FMOD_DSP_FFT_WINDOW_HANNING,         /* w[n] = 0.5 *  (1.0  - COS(n/N) )                                                                      */
    FMOD_DSP_FFT_WINDOW_BLACKMAN,        /* w[n] = 0.42 - (0.5  * COS(n/N) ) + (0.08 * COS(2.0 * n/N) )                                           */
    FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS,  /* w[n] = 0.35875 - (0.48829 * COS(1.0 * n/N)) + (0.14128 * COS(2.0 * n/N)) - (0.01168 * COS(3.0 * n/N)) */
    
    FMOD_DSP_FFT_WINDOW_MAX,             /* Maximum number of FFT window types supported. */
    FMOD_DSP_FFT_WINDOW_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_DSP_FFT_WINDOW;


/*
[ENUM]
[
    [DESCRIPTION]   
    List of interpolation types that the FMOD Ex software mixer supports.  

    [REMARKS]
    The default resampler type is FMOD_DSP_RESAMPLER_LINEAR.
    Use System::setSoftwareFormat to tell FMOD the resampling quality you require for FMOD_SOFTWARE based sounds.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    System::setSoftwareFormat
    System::getSoftwareFormat
]
*/
typedef enum
{
    FMOD_DSP_RESAMPLER_NOINTERP,        /* No interpolation.  High frequency aliasing hiss will be audible depending on the sample rate of the sound. */
    FMOD_DSP_RESAMPLER_LINEAR,          /* Linear interpolation (default method).  Fast and good quality, causes very slight lowpass effect on low frequency sounds. */
    FMOD_DSP_RESAMPLER_CUBIC,           /* Cubic interoplation.  Slower than linear interpolation but better quality. */
    FMOD_DSP_RESAMPLER_SPLINE,          /* 5 point spline interoplation.  Slowest resampling method but best quality. */

    FMOD_DSP_RESAMPLER_MAX,             /* Maximum number of resample methods supported. */
    FMOD_DSP_RESAMPLER_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_DSP_RESAMPLER;


/*
[ENUM]
[
    [DESCRIPTION]   
    List of tag types that could be stored within a sound.  These include id3 tags, metadata from netstreams and vorbis/asf data.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    Sound::getTag
]
*/
typedef enum
{
    FMOD_TAGTYPE_UNKNOWN = 0,
    FMOD_TAGTYPE_ID3V1,
    FMOD_TAGTYPE_ID3V2,
    FMOD_TAGTYPE_VORBISCOMMENT,
    FMOD_TAGTYPE_SHOUTCAST,
    FMOD_TAGTYPE_ICECAST,
    FMOD_TAGTYPE_ASF,
    FMOD_TAGTYPE_MIDI,
    FMOD_TAGTYPE_PLAYLIST,
    FMOD_TAGTYPE_FMOD,
    FMOD_TAGTYPE_USER,

    FMOD_TAGTYPE_MAX,               /* Maximum number of tag types supported. */
    FMOD_TAGTYPE_FORCEINT = 65536   /* Makes sure this enum is signed 32bit. */
} FMOD_TAGTYPE;


/*
[ENUM]
[
    [DESCRIPTION]   
    List of data types that can be returned by Sound::getTag

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    Sound::getTag
]
*/
typedef enum
{
    FMOD_TAGDATATYPE_BINARY = 0,
    FMOD_TAGDATATYPE_INT,
    FMOD_TAGDATATYPE_FLOAT,
    FMOD_TAGDATATYPE_STRING,
    FMOD_TAGDATATYPE_STRING_UTF16,
    FMOD_TAGDATATYPE_STRING_UTF16BE,
    FMOD_TAGDATATYPE_STRING_UTF8,
    FMOD_TAGDATATYPE_CDTOC,

    FMOD_TAGDATATYPE_MAX,               /* Maximum number of tag datatypes supported. */
    FMOD_TAGDATATYPE_FORCEINT = 65536   /* Makes sure this enum is signed 32bit. */
} FMOD_TAGDATATYPE;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a piece of tag data.

    [REMARKS]
    Members marked with [in] mean the user sets the value before passing it to the function.
    Members marked with [out] mean FMOD sets the value to be used after the function exits.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    Sound::getTag
    FMOD_TAGTYPE
    FMOD_TAGDATATYPE
]
*/
typedef struct FMOD_TAG
{
    FMOD_TAGTYPE      type;         /* [out] The type of this tag. */
    FMOD_TAGDATATYPE  datatype;     /* [out] The type of data that this tag contains */
    char             *name;         /* [out] The name of this tag i.e. "TITLE", "ARTIST" etc. */
    void             *data;         /* [out] Pointer to the tag data - its format is determined by the datatype member */
    unsigned int      datalen;      /* [out] Length of the data contained in this tag */
    FMOD_BOOL         updated;      /* [out] True if this tag has been updated since last being accessed with Sound::getTag */
} FMOD_TAG;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Structure describing a CD/DVD table of contents

    [REMARKS]
    Members marked with [in] mean the user sets the value before passing it to the function.
    Members marked with [out] mean FMOD sets the value to be used after the function exits.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    Sound::getTag
]
*/
typedef struct FMOD_CDTOC
{
    int numtracks;                  /* [out] The number of tracks on the CD */
    int min[100];                   /* [out] The start offset of each track in minutes */
    int sec[100];                   /* [out] The start offset of each track in seconds */
    int frame[100];                 /* [out] The start offset of each track in frames */
} FMOD_CDTOC;


/*
[DEFINE]
[
    [NAME]
    FMOD_TIMEUNIT

    [DESCRIPTION]   
    List of time types that can be returned by Sound::getLength and used with Channel::setPosition or Channel::getPosition.

    [REMARKS]
    FMOD_TIMEUNIT_SENTENCE_MS, FMOD_TIMEUNIT_SENTENCE_PCM, FMOD_TIMEUNIT_SENTENCE_PCMBYTES, FMOD_TIMEUNIT_SENTENCE and FMOD_TIMEUNIT_SENTENCE_SUBSOUND are only supported by Channel functions.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]      
    Sound::getLength
    Channel::setPosition
    Channel::getPosition
]
*/
#define FMOD_TIMEUNIT_MS                0x00000001  /* Milliseconds. */
#define FMOD_TIMEUNIT_PCM               0x00000002  /* PCM Samples, related to milliseconds * samplerate / 1000. */
#define FMOD_TIMEUNIT_PCMBYTES          0x00000004  /* Bytes, related to PCM samples * channels * datawidth (ie 16bit = 2 bytes). */
#define FMOD_TIMEUNIT_RAWBYTES          0x00000008  /* Raw file bytes of (compressed) sound data (does not include headers).  Only used by Sound::getLength and Channel::getPosition. */
#define FMOD_TIMEUNIT_MODORDER          0x00000100  /* MOD/S3M/XM/IT.  Order in a sequenced module format.  Use Sound::getFormat to determine the PCM format being decoded to. */
#define FMOD_TIMEUNIT_MODROW            0x00000200  /* MOD/S3M/XM/IT.  Current row in a sequenced module format.  Sound::getLength will return the number of rows in the currently playing or seeked to pattern. */
#define FMOD_TIMEUNIT_MODPATTERN        0x00000400  /* MOD/S3M/XM/IT.  Current pattern in a sequenced module format.  Sound::getLength will return the number of patterns in the song and Channel::getPosition will return the currently playing pattern. */
#define FMOD_TIMEUNIT_SENTENCE_MS       0x00010000  /* Currently playing subsound in a sentence time in milliseconds. */
#define FMOD_TIMEUNIT_SENTENCE_PCM      0x00020000  /* Currently playing subsound in a sentence time in PCM Samples, related to milliseconds * samplerate / 1000. */
#define FMOD_TIMEUNIT_SENTENCE_PCMBYTES 0x00040000  /* Currently playing subsound in a sentence time in bytes, related to PCM samples * channels * datawidth (ie 16bit = 2 bytes). */
#define FMOD_TIMEUNIT_SENTENCE          0x00080000  /* Currently playing sentence index according to the channel. */
#define FMOD_TIMEUNIT_SENTENCE_SUBSOUND 0x00100000  /* Currently playing subsound index in a sentence. */
#define FMOD_TIMEUNIT_BUFFERED          0x10000000  /* Time value as seen by buffered stream.  This is always ahead of audible time, and is only used for processing. */
/* [DEFINE_END] */


typedef FMOD_RESULT (F_CALLBACK *FMOD_SOUND_NONBLOCKCALLBACK)(FMOD_SOUND *sound, FMOD_RESULT result);
typedef FMOD_RESULT (F_CALLBACK *FMOD_SOUND_PCMREADCALLBACK)(FMOD_SOUND *sound, void *data, unsigned int datalen);
typedef FMOD_RESULT (F_CALLBACK *FMOD_SOUND_PCMSETPOSCALLBACK)(FMOD_SOUND *sound, int subsound, unsigned int position, FMOD_TIMEUNIT postype);


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Use this structure with System::createSound when more control is needed over loading.
    The possible reasons to use this with System::createSound are:
    - Loading a file from memory.
    - Loading a file from within another larger (possibly wad/pak) file, by giving the loader an offset and length.
    - To create a user created / non file based sound.
    - To specify a starting subsound to seek to within a multi-sample sounds (ie FSB/DLS/SF2) when created as a stream.
    - To specify which subsounds to load for multi-sample sounds (ie FSB/DLS/SF2) so that memory is saved and only a subset is actually loaded/read from disk.
    - To specify 'piggyback' read and seek callbacks for capture of sound data as fmod reads and decodes it.  Useful for ripping decoded PCM data from sounds as they are loaded / played.
    - To specify a MIDI DLS/SF2 sample set file to load when opening a MIDI file.
    See below on what members to fill for each of the above types of sound you want to create.

    [REMARKS]
    This structure is optional!  Specify 0 or NULL in System::createSound if you don't need it!
    
    Members marked with [in] mean the user sets the value before passing it to the function.
    Members marked with [out] mean FMOD sets the value to be used after the function exits.
    
    <u>Loading a file from memory.</u>
    - Create the sound using the FMOD_OPENMEMORY flag.
    - Mandatory.  Specify 'length' for the size of the memory block in bytes.
    - Other flags are optional.
    
    
    <u>Loading a file from within another larger (possibly wad/pak) file, by giving the loader an offset and length.</u>
    - Mandatory.  Specify 'fileoffset' and 'length'.
    - Other flags are optional.
    
    
    <u>To create a user created / non file based sound.</u>
    - Create the sound using the FMOD_OPENUSER flag.
    - Mandatory.  Specify 'defaultfrequency, 'numchannels' and 'format'.
    - Other flags are optional.
    
    
    <u>To specify a starting subsound to seek to and flush with, within a multi-sample stream (ie FSB/DLS/SF2).</u>
    
    - Mandatory.  Specify 'initialsubsound'.
    
    
    <u>To specify which subsounds to load for multi-sample sounds (ie FSB/DLS/SF2) so that memory is saved and only a subset is actually loaded/read from disk.</u>
    
    - Mandatory.  Specify 'inclusionlist' and 'inclusionlistnum'.
    
    
    <u>To specify 'piggyback' read and seek callbacks for capture of sound data as fmod reads and decodes it.  Useful for ripping decoded PCM data from sounds as they are loaded / played.</u>
    
    - Mandatory.  Specify 'pcmreadcallback' and 'pcmseekcallback'.
    
    
    <u>To specify a MIDI DLS/SF2 sample set file to load when opening a MIDI file.</u>
    
    - Mandatory.  Specify 'dlsname'.
    
    
    Setting the 'decodebuffersize' is for cpu intensive codecs that may be causing stuttering, not file intensive codecs (ie those from CD or netstreams) which are normally altered with System::setStreamBufferSize.  As an example of cpu intensive codecs, an mp3 file will take more cpu to decode than a PCM wav file.
    If you have a stuttering effect, then it is using more cpu than the decode buffer playback rate can keep up with.  Increasing the decode buffersize will most likely solve this problem.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::createSound
    System::setStreamBufferSize
    FMOD_MODE
]
*/
typedef struct FMOD_CREATESOUNDEXINFO
{
    int                            cbsize;             /* [in] Size of this structure.  This is used so the structure can be expanded in the future and still work on older versions of FMOD Ex. */
    unsigned int                   length;             /* [in] Optional. Specify 0 to ignore. Size in bytes of file to load, or sound to create (in this case only if FMOD_OPENUSER is used).  Required if loading from memory.  If 0 is specified, then it will use the size of the file (unless loading from memory then an error will be returned). */
    unsigned int                   fileoffset;         /* [in] Optional. Specify 0 to ignore. Offset from start of the file to start loading from.  This is useful for loading files from inside big data files. */
    int                            numchannels;        /* [in] Optional. Specify 0 to ignore. Number of channels in a sound mandatory if FMOD_OPENUSER or FMOD_OPENRAW is used. */
    int                            defaultfrequency;   /* [in] Optional. Specify 0 to ignore. Default frequency of sound in a sound mandatory if FMOD_OPENUSER or FMOD_OPENRAW is used.  Other formats use the frequency determined by the file format. */
    FMOD_SOUND_FORMAT              format;             /* [in] Optional. Specify 0 or FMOD_SOUND_FORMAT_NONE to ignore. Format of the sound mandatory if FMOD_OPENUSER or FMOD_OPENRAW is used.  Other formats use the format determined by the file format.   */
    unsigned int                   decodebuffersize;   /* [in] Optional. Specify 0 to ignore. For streams.  This determines the size of the double buffer (in PCM samples) that a stream uses.  Use this for user created streams if you want to determine the size of the callback buffer passed to you.  Specify 0 to use FMOD's default size which is currently equivalent to 400ms of the sound format created/loaded. */
    int                            initialsubsound;    /* [in] Optional. Specify 0 to ignore. In a multi-sample file format such as .FSB/.DLS/.SF2, specify the initial subsound to seek to, only if FMOD_CREATESTREAM is used. */
    int                            numsubsounds;       /* [in] Optional. Specify 0 to ignore or have no subsounds.  In a user created multi-sample sound, specify the number of subsounds within the sound that are accessable with Sound::getSubSound. */
    int                           *inclusionlist;      /* [in] Optional. Specify 0 to ignore. In a multi-sample format such as .FSB/.DLS/.SF2 it may be desirable to specify only a subset of sounds to be loaded out of the whole file.  This is an array of subsound indices to load into memory when created. */
    int                            inclusionlistnum;   /* [in] Optional. Specify 0 to ignore. This is the number of integers contained within the inclusionlist array. */
    FMOD_SOUND_PCMREADCALLBACK     pcmreadcallback;    /* [in] Optional. Specify 0 to ignore. Callback to 'piggyback' on FMOD's read functions and accept or even write PCM data while FMOD is opening the sound.  Used for user sounds created with FMOD_OPENUSER or for capturing decoded data as FMOD reads it. */
    FMOD_SOUND_PCMSETPOSCALLBACK   pcmsetposcallback;  /* [in] Optional. Specify 0 to ignore. Callback for when the user calls a seeking function such as Channel::setTime or Channel::setPosition within a multi-sample sound, and for when it is opened.*/
    FMOD_SOUND_NONBLOCKCALLBACK    nonblockcallback;   /* [in] Optional. Specify 0 to ignore. Callback for successful completion, or error while loading a sound that used the FMOD_NONBLOCKING flag.*/
    const char                    *dlsname;            /* [in] Optional. Specify 0 to ignore. Filename for a DLS or SF2 sample set when loading a MIDI file.   If not specified, on windows it will attempt to open /windows/system32/drivers/gm.dls, otherwise the MIDI will fail to open.  */
    const char                    *encryptionkey;      /* [in] Optional. Specify 0 to ignore. Key for encrypted FSB file.  Without this key an encrypted FSB file will not load. */
    int                            maxpolyphony;       /* [in] Optional. Specify 0 to ignore. For sequenced formats with dynamic channel allocation such as .MID and .IT, this specifies the maximum voice count allowed while playing.  .IT defaults to 64.  .MID defaults to 32. */
    void                          *userdata;           /* [in] Optional. Specify 0 to ignore. This is user data to be attached to the sound during creation.  Access via Sound::getUserData. */
    FMOD_SOUND_TYPE                suggestedsoundtype; /* [in] Optional. Specify 0 or FMOD_SOUND_TYPE_UNKNOWN to ignore.  Instead of scanning all codec types, use this to speed up loading by making it jump straight to this codec. */
} FMOD_CREATESOUNDEXINFO;


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Structure defining a reverb environment.
    
    For more indepth descriptions of the reverb properties under win32, please see the EAX2 and EAX3
    documentation at http://developer.creative.com/ under the 'downloads' section.
    If they do not have the EAX3 documentation, then most information can be attained from
    the EAX2 documentation, as EAX3 only adds some more parameters and functionality on top of 
    EAX2.

    [REMARKS]
    Note the default reverb properties are the same as the FMOD_PRESET_GENERIC preset.
    Note that integer values that typically range from -10,000 to 1000 are represented in 
    decibels, and are of a logarithmic scale, not linear, wheras float values are always linear.
    PORTABILITY: Each member has the platform it supports in braces ie (win32/Xbox).  
    Some reverb parameters are only supported in win32 and some only on Xbox. If all parameters are set then
    the reverb should product a similar effect on either platform.
    Win32/Win64 - This is only supported with FMOD_OUTPUTTYPE_DSOUND and EAX/I3DL2 compatible sound cards. 
    Xbox - A subset of parameters are supported.  
    Xbox360 - A subset of parameters are supported.  
    PlayStation 2 - Only the Environment and Flags paramenters are supported. 
    GameCube - Only a subset of parameters are supported. 
    Wii - Only a subset of parameters are supported. 
    Software - Only 'Room' is supported.
    
    The numerical values listed below are the maximum, minimum and default values for each variable respectively.
    
    Members marked with [in] mean the user sets the value before passing it to the function.
    Members marked with [out] mean FMOD sets the value to be used after the function exits.

    [PLATFORMS]
    Win32, Win64, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::setReverbProperties
    System::getReverbProperties
    FMOD_REVERB_PRESETS
    FMOD_REVERB_FLAGS
]
*/
typedef struct FMOD_REVERB_PROPERTIES
{                                   /*          MIN     MAX     DEFAULT  DESCRIPTION */
    int          Instance;          /* [in]     0     , 2     , 0      , EAX4/GameCube/Wii only. Environment Instance. 3 (2 for GameCube) seperate reverbs simultaneously are possible. This specifies which one to set. (win32/GameCube/Wii) */
    int          Environment;       /* [in/out] -1    , 25    , -1     , sets all listener properties.  -1 = OFF. (win32/ps2) */
    float        EnvSize;           /* [in/out] 1.0   , 100.0 , 7.5    , environment size in meters (win32 only) */
    float        EnvDiffusion;      /* [in/out] 0.0   , 1.0   , 1.0    , environment diffusion (win32/Xbox/GameCube) */
    int          Room;              /* [in/out] -10000, 0     , -1000  , room effect level (at mid frequencies) (win32/Xbox/Xbox 360/GameCube/software) */
    int          RoomHF;            /* [in/out] -10000, 0     , -100   , relative room effect level at high frequencies (win32/Xbox/Xbox 360) */
    int          RoomLF;            /* [in/out] -10000, 0     , 0      , relative room effect level at low frequencies (win32 only) */
    float        DecayTime;         /* [in/out] 0.1   , 20.0  , 1.49   , reverberation decay time at mid frequencies (win32/Xbox/Xbox 360/GameCube) */
    float        DecayHFRatio;      /* [in/out] 0.1   , 2.0   , 0.83   , high-frequency to mid-frequency decay time ratio (win32/Xbox/Xbox 360) */
    float        DecayLFRatio;      /* [in/out] 0.1   , 2.0   , 1.0    , low-frequency to mid-frequency decay time ratio (win32 only) */
    int          Reflections;       /* [in/out] -10000, 1000  , -2602  , early reflections level relative to room effect (win32/Xbox/Xbox 360/GameCube) */
    float        ReflectionsDelay;  /* [in/out] 0.0   , 0.3   , 0.007  , initial reflection delay time (win32/Xbox/Xbox 360) */
    float        ReflectionsPan[3]; /* [in/out]       ,       , [0,0,0], early reflections panning vector (win32 only) */
    int          Reverb;            /* [in/out] -10000, 2000  , 200    , late reverberation level relative to room effect (win32/Xbox/Xbox 360) */
    float        ReverbDelay;       /* [in/out] 0.0   , 0.1   , 0.011  , late reverberation delay time relative to initial reflection (win32/Xbox/Xbox 360/GameCube) */
    float        ReverbPan[3];      /* [in/out]       ,       , [0,0,0], late reverberation panning vector (win32 only) */
    float        EchoTime;          /* [in/out] .075  , 0.25  , 0.25   , echo time (win32 or ps2 FMOD_PRESET_PS2_ECHO/FMOD_PRESET_PS2_DELAY only) */
    float        EchoDepth;         /* [in/out] 0.0   , 1.0   , 0.0    , echo depth (win32 or ps2 FMOD_PRESET_PS2_ECHO only) */
    float        ModulationTime;    /* [in/out] 0.04  , 4.0   , 0.25   , modulation time (win32 only) */
    float        ModulationDepth;   /* [in/out] 0.0   , 1.0   , 0.0    , modulation depth (win32/GameCube) */
    float        AirAbsorptionHF;   /* [in/out] -100  , 0.0   , -5.0   , change in level per meter at high frequencies (win32 only) */
    float        HFReference;       /* [in/out] 1000.0, 20000 , 5000.0 , reference high frequency (hz) (win32/Xbox/Xbox 360) */
    float        LFReference;       /* [in/out] 20.0  , 1000.0, 250.0  , reference low frequency (hz) (win32 only) */
    float        RoomRolloffFactor; /* [in/out] 0.0   , 10.0  , 0.0    , like rolloffscale in System::set3DSettings but for reverb room size effect (win32/Xbox/Xbox 360) */
    float        Diffusion;         /* [in/out] 0.0   , 100.0 , 100.0  , Value that controls the echo density in the late reverberation decay. (Xbox/Xbox 360) */
    float        Density;           /* [in/out] 0.0   , 100.0 , 100.0  , Value that controls the modal density in the late reverberation decay (Xbox/Xbox 360) */
    unsigned int Flags;             /* [in/out] FMOD_REVERB_FLAGS - modifies the behavior of above properties (win32/ps2) */
} FMOD_REVERB_PROPERTIES;


/*
[DEFINE] 
[
    [NAME] 
    FMOD_REVERB_FLAGS

    [DESCRIPTION]
    Values for the Flags member of the FMOD_REVERB_PROPERTIES structure.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation 3

    [SEE_ALSO]
    FMOD_REVERB_PROPERTIES
]
*/
#define FMOD_REVERB_FLAGS_DECAYTIMESCALE        0x00000001 /* 'EnvSize' affects reverberation decay time */
#define FMOD_REVERB_FLAGS_REFLECTIONSSCALE      0x00000002 /* 'EnvSize' affects reflection level */
#define FMOD_REVERB_FLAGS_REFLECTIONSDELAYSCALE 0x00000004 /* 'EnvSize' affects initial reflection delay time */
#define FMOD_REVERB_FLAGS_REVERBSCALE           0x00000008 /* 'EnvSize' affects reflections level */
#define FMOD_REVERB_FLAGS_REVERBDELAYSCALE      0x00000010 /* 'EnvSize' affects late reverberation delay time */
#define FMOD_REVERB_FLAGS_DECAYHFLIMIT          0x00000020 /* AirAbsorptionHF affects DecayHFRatio */
#define FMOD_REVERB_FLAGS_ECHOTIMESCALE         0x00000040 /* 'EnvSize' affects echo time */
#define FMOD_REVERB_FLAGS_MODULATIONTIMESCALE   0x00000080 /* 'EnvSize' affects modulation time */
#define FMOD_REVERB_FLAGS_CORE0                 0x00000100 /* PS2 Only - Reverb is applied to CORE0 (hw voices 0-23) */
#define FMOD_REVERB_FLAGS_CORE1                 0x00000200 /* PS2 Only - Reverb is applied to CORE1 (hw voices 24-47) */
#define FMOD_REVERB_FLAGS_HIGHQUALITYREVERB     0x00000400 /* GameCube/Wii. Use high quality reverb */
#define FMOD_REVERB_FLAGS_HIGHQUALITYDPL2REVERB 0x00000800 /* GameCube/Wii. Use high quality DPL2 reverb */

#define FMOD_REVERB_FLAGS_DEFAULT              (FMOD_REVERB_FLAGS_DECAYTIMESCALE |        \
                                                FMOD_REVERB_FLAGS_REFLECTIONSSCALE |      \
                                                FMOD_REVERB_FLAGS_REFLECTIONSDELAYSCALE | \
                                                FMOD_REVERB_FLAGS_REVERBSCALE |           \
                                                FMOD_REVERB_FLAGS_REVERBDELAYSCALE |      \
                                                FMOD_REVERB_FLAGS_DECAYHFLIMIT |          \
                                                FMOD_REVERB_FLAGS_CORE0 |                 \
                                                FMOD_REVERB_FLAGS_CORE1)
/* [DEFINE_END] */


/*
[DEFINE] 
[
    [NAME] 
    FMOD_REVERB_PRESETS

    [DESCRIPTION]   
    A set of predefined environment PARAMETERS, created by Creative Labs
    These are used to initialize an FMOD_REVERB_PROPERTIES structure statically.
    ie 
    FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_GENERIC;

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::setReverbProperties
]
*/
/*                                    Inst Env  Size    Diffus  Room   RoomHF  RmLF DecTm   DecHF  DecLF   Refl  RefDel  RefPan               Revb  RevDel  ReverbPan           EchoTm  EchDp  ModTm  ModDp  AirAbs  HFRef    LFRef  RRlOff Diffus  Densty  FLAGS */
#define FMOD_PRESET_OFF              {  0, -1,  7.5f,   1.00f, -10000, -10000, 0,   1.00f,  1.00f, 1.0f,  -2602, 0.007f, { 0.0f,0.0f,0.0f },   200, 0.011f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f,   0.0f,   0.0f, 0x33f }
#define FMOD_PRESET_GENERIC          {  0,  0,  7.5f,   1.00f, -1000,  -100,   0,   1.49f,  0.83f, 1.0f,  -2602, 0.007f, { 0.0f,0.0f,0.0f },   200, 0.011f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_PADDEDCELL       {  0,  1,  1.4f,   1.00f, -1000,  -6000,  0,   0.17f,  0.10f, 1.0f,  -1204, 0.001f, { 0.0f,0.0f,0.0f },   207, 0.002f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_ROOM             {  0,  2,  1.9f,   1.00f, -1000,  -454,   0,   0.40f,  0.83f, 1.0f,  -1646, 0.002f, { 0.0f,0.0f,0.0f },    53, 0.003f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_BATHROOM         {  0,  3,  1.4f,   1.00f, -1000,  -1200,  0,   1.49f,  0.54f, 1.0f,   -370, 0.007f, { 0.0f,0.0f,0.0f },  1030, 0.011f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f,  60.0f, 0x3f }
#define FMOD_PRESET_LIVINGROOM       {  0,  4,  2.5f,   1.00f, -1000,  -6000,  0,   0.50f,  0.10f, 1.0f,  -1376, 0.003f, { 0.0f,0.0f,0.0f }, -1104, 0.004f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_STONEROOM        {  0,  5,  11.6f,  1.00f, -1000,  -300,   0,   2.31f,  0.64f, 1.0f,   -711, 0.012f, { 0.0f,0.0f,0.0f },    83, 0.017f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_AUDITORIUM       {  0,  6,  21.6f,  1.00f, -1000,  -476,   0,   4.32f,  0.59f, 1.0f,   -789, 0.020f, { 0.0f,0.0f,0.0f },  -289, 0.030f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_CONCERTHALL      {  0,  7,  19.6f,  1.00f, -1000,  -500,   0,   3.92f,  0.70f, 1.0f,  -1230, 0.020f, { 0.0f,0.0f,0.0f },    -2, 0.029f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_CAVE             {  0,  8,  14.6f,  1.00f, -1000,  0,      0,   2.91f,  1.30f, 1.0f,   -602, 0.015f, { 0.0f,0.0f,0.0f },  -302, 0.022f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x1f }
#define FMOD_PRESET_ARENA            {  0,  9,  36.2f,  1.00f, -1000,  -698,   0,   7.24f,  0.33f, 1.0f,  -1166, 0.020f, { 0.0f,0.0f,0.0f },    16, 0.030f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_HANGAR           {  0,  10, 50.3f,  1.00f, -1000,  -1000,  0,   10.05f, 0.23f, 1.0f,   -602, 0.020f, { 0.0f,0.0f,0.0f },   198, 0.030f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_CARPETTEDHALLWAY {  0,  11, 1.9f,   1.00f, -1000,  -4000,  0,   0.30f,  0.10f, 1.0f,  -1831, 0.002f, { 0.0f,0.0f,0.0f }, -1630, 0.030f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_HALLWAY          {  0,  12, 1.8f,   1.00f, -1000,  -300,   0,   1.49f,  0.59f, 1.0f,  -1219, 0.007f, { 0.0f,0.0f,0.0f },   441, 0.011f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_STONECORRIDOR    {  0,  13, 13.5f,  1.00f, -1000,  -237,   0,   2.70f,  0.79f, 1.0f,  -1214, 0.013f, { 0.0f,0.0f,0.0f },   395, 0.020f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_ALLEY            {  0,  14, 7.5f,   0.30f, -1000,  -270,   0,   1.49f,  0.86f, 1.0f,  -1204, 0.007f, { 0.0f,0.0f,0.0f },    -4, 0.011f, { 0.0f,0.0f,0.0f }, 0.125f, 0.95f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_FOREST           {  0,  15, 38.0f,  0.30f, -1000,  -3300,  0,   1.49f,  0.54f, 1.0f,  -2560, 0.162f, { 0.0f,0.0f,0.0f },  -229, 0.088f, { 0.0f,0.0f,0.0f }, 0.125f, 1.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f,  79.0f, 100.0f, 0x3f }
#define FMOD_PRESET_CITY             {  0,  16, 7.5f,   0.50f, -1000,  -800,   0,   1.49f,  0.67f, 1.0f,  -2273, 0.007f, { 0.0f,0.0f,0.0f }, -1691, 0.011f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f,  50.0f, 100.0f, 0x3f }
#define FMOD_PRESET_MOUNTAINS        {  0,  17, 100.0f, 0.27f, -1000,  -2500,  0,   1.49f,  0.21f, 1.0f,  -2780, 0.300f, { 0.0f,0.0f,0.0f }, -1434, 0.100f, { 0.0f,0.0f,0.0f }, 0.250f, 1.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f,  27.0f, 100.0f, 0x1f }
#define FMOD_PRESET_QUARRY           {  0,  18, 17.5f,  1.00f, -1000,  -1000,  0,   1.49f,  0.83f, 1.0f, -10000, 0.061f, { 0.0f,0.0f,0.0f },   500, 0.025f, { 0.0f,0.0f,0.0f }, 0.125f, 0.70f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }
#define FMOD_PRESET_PLAIN            {  0,  19, 42.5f,  0.21f, -1000,  -2000,  0,   1.49f,  0.50f, 1.0f,  -2466, 0.179f, { 0.0f,0.0f,0.0f }, -1926, 0.100f, { 0.0f,0.0f,0.0f }, 0.250f, 1.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f,  21.0f, 100.0f, 0x3f }
#define FMOD_PRESET_PARKINGLOT       {  0,  20, 8.3f,   1.00f, -1000,  0,      0,   1.65f,  1.50f, 1.0f,  -1363, 0.008f, { 0.0f,0.0f,0.0f }, -1153, 0.012f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x1f }
#define FMOD_PRESET_SEWERPIPE        {  0,  21, 1.7f,   0.80f, -1000,  -1000,  0,   2.81f,  0.14f, 1.0f,    429, 0.014f, { 0.0f,0.0f,0.0f },  1023, 0.021f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 0.000f, -5.0f, 5000.0f, 250.0f, 0.0f,  80.0f,  60.0f, 0x3f }
#define FMOD_PRESET_UNDERWATER       {  0,  22, 1.8f,   1.00f, -1000,  -4000,  0,   1.49f,  0.10f, 1.0f,   -449, 0.007f, { 0.0f,0.0f,0.0f },  1700, 0.011f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 1.18f, 0.348f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x3f }

/* Non I3DL2 presets */

#define FMOD_PRESET_DRUGGED          {  0,  23, 1.9f,   0.50f, -1000,  0,      0,   8.39f,  1.39f, 1.0f,  -115,  0.002f, { 0.0f,0.0f,0.0f },   985, 0.030f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.25f, 1.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x1f }
#define FMOD_PRESET_DIZZY            {  0,  24, 1.8f,   0.60f, -1000,  -400,   0,   17.23f, 0.56f, 1.0f,  -1713, 0.020f, { 0.0f,0.0f,0.0f },  -613, 0.030f, { 0.0f,0.0f,0.0f }, 0.250f, 1.00f, 0.81f, 0.310f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x1f }
#define FMOD_PRESET_PSYCHOTIC        {  0,  25, 1.0f,   0.50f, -1000,  -151,   0,   7.56f,  0.91f, 1.0f,  -626,  0.020f, { 0.0f,0.0f,0.0f },   774, 0.030f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 4.00f, 1.000f, -5.0f, 5000.0f, 250.0f, 0.0f, 100.0f, 100.0f, 0x1f }

/* PlayStation 2 Only presets */

#define FMOD_PRESET_PS2_ROOM         {  0,  1,  0,      0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f, { 0.0f,0.0f,0.0f },     0, 0.000f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.00f, 0.000f,  0.0f, 0000.0f,   0.0f, 0.0f,   0.0f,   0.0f, 0x31f }
#define FMOD_PRESET_PS2_STUDIO_A     {  0,  2,  0,      0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f, { 0.0f,0.0f,0.0f },     0, 0.000f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.00f, 0.000f,  0.0f, 0000.0f,   0.0f, 0.0f,   0.0f,   0.0f, 0x31f }
#define FMOD_PRESET_PS2_STUDIO_B     {  0,  3,  0,      0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f, { 0.0f,0.0f,0.0f },     0, 0.000f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.00f, 0.000f,  0.0f, 0000.0f,   0.0f, 0.0f,   0.0f,   0.0f, 0x31f }
#define FMOD_PRESET_PS2_STUDIO_C     {  0,  4,  0,      0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f, { 0.0f,0.0f,0.0f },     0, 0.000f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.00f, 0.000f,  0.0f, 0000.0f,   0.0f, 0.0f,   0.0f,   0.0f, 0x31f }
#define FMOD_PRESET_PS2_HALL         {  0,  5,  0,      0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f, { 0.0f,0.0f,0.0f },     0, 0.000f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.00f, 0.000f,  0.0f, 0000.0f,   0.0f, 0.0f,   0.0f,   0.0f, 0x31f }
#define FMOD_PRESET_PS2_SPACE        {  0,  6,  0,      0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f, { 0.0f,0.0f,0.0f },     0, 0.000f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.00f, 0.000f,  0.0f, 0000.0f,   0.0f, 0.0f,   0.0f,   0.0f, 0x31f }
#define FMOD_PRESET_PS2_ECHO         {  0,  7,  0,      0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f, { 0.0f,0.0f,0.0f },     0, 0.000f, { 0.0f,0.0f,0.0f }, 0.250f, 0.75f, 0.00f, 0.000f,  0.0f, 0000.0f,   0.0f, 0.0f,   0.0f,   0.0f, 0x31f }
#define FMOD_PRESET_PS2_DELAY        {  0,  8,  0,      0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f, { 0.0f,0.0f,0.0f },     0, 0.000f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.00f, 0.000f,  0.0f, 0000.0f,   0.0f, 0.0f,   0.0f,   0.0f, 0x31f }
#define FMOD_PRESET_PS2_PIPE         {  0,  9,  0,      0,     0,      0,      0,   0.0f,   0.0f,  0.0f,     0,  0.000f, { 0.0f,0.0f,0.0f },     0, 0.000f, { 0.0f,0.0f,0.0f }, 0.250f, 0.00f, 0.00f, 0.000f,  0.0f, 0000.0f,   0.0f, 0.0f,   0.0f,   0.0f, 0x31f }
/* [DEFINE_END] */


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Structure defining the properties for a reverb source, related to a FMOD channel.
    
    For more indepth descriptions of the reverb properties under win32, please see the EAX3
    documentation at http://developer.creative.com/ under the 'downloads' section.
    If they do not have the EAX3 documentation, then most information can be attained from
    the EAX2 documentation, as EAX3 only adds some more parameters and functionality on top of 
    EAX2.
    
    Note the default reverb properties are the same as the FMOD_PRESET_GENERIC preset.
    Note that integer values that typically range from -10,000 to 1000 are represented in 
    decibels, and are of a logarithmic scale, not linear, wheras float values are typically linear.
    PORTABILITY: Each member has the platform it supports in braces ie (win32/Xbox).
    Some reverb parameters are only supported in win32 and some only on Xbox. If all parameters are set then
    the reverb should product a similar effect on either platform.
    
    The numerical values listed below are the maximum, minimum and default values for each variable respectively.

    [REMARKS]

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    Channel::setReverbProperties
    Channel::getReverbProperties
    FMOD_REVERB_CHANNELFLAGS 
]
*/
typedef struct FMOD_REVERB_CHANNELPROPERTIES  
{                                      /*          MIN     MAX    DEFAULT  DESCRIPTION */
    int          Direct;               /* [in/out] -10000, 1000,  0,       direct path level (at low and mid frequencies) (win32/Xbox) */
    int          DirectHF;             /* [in/out] -10000, 0,     0,       relative direct path level at high frequencies (win32/Xbox) */
    int          Room;                 /* [in/out] -10000, 1000,  0,       room effect level (at low and mid frequencies) (win32/Xbox/Gamecube/Xbox360) */
    int          RoomHF;               /* [in/out] -10000, 0,     0,       relative room effect level at high frequencies (win32/Xbox) */
    int          Obstruction;          /* [in/out] -10000, 0,     0,       main obstruction control (attenuation at high frequencies)  (win32/Xbox) */
    float        ObstructionLFRatio;   /* [in/out] 0.0,    1.0,   0.0,     obstruction low-frequency level re. main control (win32/Xbox) */
    int          Occlusion;            /* [in/out] -10000, 0,     0,       main occlusion control (attenuation at high frequencies) (win32/Xbox) */
    float        OcclusionLFRatio;     /* [in/out] 0.0,    1.0,   0.25,    occlusion low-frequency level re. main control (win32/Xbox) */
    float        OcclusionRoomRatio;   /* [in/out] 0.0,    10.0,  1.5,     relative occlusion control for room effect (win32) */
    float        OcclusionDirectRatio; /* [in/out] 0.0,    10.0,  1.0,     relative occlusion control for direct path (win32) */
    int          Exclusion;            /* [in/out] -10000, 0,     0,       main exlusion control (attenuation at high frequencies) (win32) */
    float        ExclusionLFRatio;     /* [in/out] 0.0,    1.0,   1.0,     exclusion low-frequency level re. main control (win32) */
    int          OutsideVolumeHF;      /* [in/out] -10000, 0,     0,       outside sound cone level at high frequencies (win32) */
    float        DopplerFactor;        /* [in/out] 0.0,    10.0,  0.0,     like DS3D flDopplerFactor but per source (win32) */
    float        RolloffFactor;        /* [in/out] 0.0,    10.0,  0.0,     like DS3D flRolloffFactor but per source (win32) */
    float        RoomRolloffFactor;    /* [in/out] 0.0,    10.0,  0.0,     like DS3D flRolloffFactor but for room effect (win32/Xbox) */
    float        AirAbsorptionFactor;  /* [in/out] 0.0,    10.0,  1.0,     multiplies AirAbsorptionHF member of FMOD_REVERB_PROPERTIES (win32) */
    unsigned int Flags;                /* [in/out] FMOD_REVERB_CHANNELFLAGS - modifies the behavior of properties (win32) */
} FMOD_REVERB_CHANNELPROPERTIES;


/*
[DEFINE] 
[
    [NAME] 
    FMOD_REVERB_CHANNELFLAGS

    [DESCRIPTION]
    Values for the Flags member of the FMOD_REVERB_CHANNELPROPERTIES structure.

    [REMARKS]
    For EAX4 support with multiple reverb environments, set FMOD_REVERB_CHANNELFLAGS_ENVIRONMENT0,
    FMOD_REVERB_CHANNELFLAGS_ENVIRONMENT1 or/and FMOD_REVERB_CHANNELFLAGS_ENVIRONMENT2 in the flags member 
    of FMOD_REVERB_CHANNELPROPERTIES to specify which environment instance(s) to target. 
    Only up to 2 environments to target can be specified at once. Specifying three will result in an error.
    If the sound card does not support EAX4, the environment flag is ignored.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    FMOD_REVERB_CHANNELPROPERTIES
]
*/
#define FMOD_REVERB_CHANNELFLAGS_DIRECTHFAUTO  0x00000001 /* Automatic setting of 'Direct'  due to distance from listener */
#define FMOD_REVERB_CHANNELFLAGS_ROOMAUTO      0x00000002 /* Automatic setting of 'Room'  due to distance from listener */
#define FMOD_REVERB_CHANNELFLAGS_ROOMHFAUTO    0x00000004 /* Automatic setting of 'RoomHF' due to distance from listener */
#define FMOD_REVERB_CHANNELFLAGS_ENVIRONMENT0  0x00000008 /* EAX4/GameCube/Wii. Specify channel to target reverb instance 0. */
#define FMOD_REVERB_CHANNELFLAGS_ENVIRONMENT1  0x00000010 /* EAX4/GameCube/Wii. Specify channel to target reverb instance 1. */
#define FMOD_REVERB_CHANNELFLAGS_ENVIRONMENT2  0x00000020 /* EAX4/GameCube/Wii. Specify channel to target reverb instance 2. */

#define FMOD_REVERB_CHANNELFLAGS_DEFAULT       (FMOD_REVERB_CHANNELFLAGS_DIRECTHFAUTO |   \
                                                FMOD_REVERB_CHANNELFLAGS_ROOMAUTO|        \
                                                FMOD_REVERB_CHANNELFLAGS_ROOMHFAUTO|    \
                                                FMOD_REVERB_CHANNELFLAGS_ENVIRONMENT0)
/* [DEFINE_END] */


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Settings for advanced features like configuring memory and cpu usage for the FMOD_CREATECOMPRESSEDSAMPLE feature.

    [REMARKS]
    maxMPEGcodecs / maxADPCMcodecs / maxXMAcodecs will determine the maximum cpu usage of playing realtime samples.  Use this to lower potential excess cpu usage and also control memory usage.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::setAdvancedSettings
    System::getAdvancedSettings
    FMOD_MODE
]
*/
typedef struct FMOD_ADVANCEDSETTINGS
{                       
    int     cbsize;             /* Size of structure.  Use sizeof(FMOD_ADVANCEDSETTINGS) */
    int     maxMPEGcodecs;      /* For use with FMOD_CREATECOMPRESSEDSAMPLE only.  Mpeg  codecs consume 29,076 bytes per instance and this number will determine how many mpeg channels can be played simultaneously.  Default = 16. */
    int     maxADPCMcodecs;     /* For use with FMOD_CREATECOMPRESSEDSAMPLE only.  ADPCM codecs consume ?? bytes per instance and this number will determine how many ADPCM channels can be played simultaneously.  Default = 32. */
    int     maxXMAcodecs;       /* For use with FMOD_CREATECOMPRESSEDSAMPLE only.  XMA   codecs consume ?? bytes per instance and this number will determine how many XMA channels can be played simultaneously.  Default = 32.  */
} FMOD_ADVANCEDSETTINGS;


/*
[ENUM]
[
    [DESCRIPTION]
    Special channel index values for FMOD functions.

    [REMARKS]
    To get 'all' of the channels, use System::getMasterChannelGroup.

    [PLATFORMS]
    Win32, Win64, Linux, Linux64, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

    [SEE_ALSO]
    System::playSound
    System::playDSP
    System::getChannel
    System::getMasterChannelGroup
]
*/
typedef enum
{
    FMOD_CHANNEL_FREE  = -1,      /* For a channel index, FMOD chooses a free voice using the priority system. */
    FMOD_CHANNEL_REUSE = -2       /* For a channel index, re-use the channel handle that was passed in. */
} FMOD_CHANNELINDEX;

/* [DEFINE_END] */


/* 
    FMOD Callbacks
*/
typedef FMOD_RESULT (F_CALLBACK *FMOD_CHANNEL_CALLBACK)      (FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, int command, unsigned int commanddata1, unsigned int commanddata2);

typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_OPENCALLBACK)     (const char *name, int unicode, unsigned int *filesize, void **handle, void **userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_CLOSECALLBACK)    (void *handle, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_READCALLBACK)     (void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata);
typedef FMOD_RESULT (F_CALLBACK *FMOD_FILE_SEEKCALLBACK)     (void *handle, unsigned int pos, void *userdata);

typedef void *      (F_CALLBACK *FMOD_MEMORY_ALLOCCALLBACK)  (unsigned int size);
typedef void *      (F_CALLBACK *FMOD_MEMORY_REALLOCCALLBACK)(void *ptr, unsigned int size);
typedef void        (F_CALLBACK *FMOD_MEMORY_FREECALLBACK)   (void *ptr);

#include "fmod_codec.h"
#include "fmod_dsp.h"

/* ========================================================================================== */
/* FUNCTION PROTOTYPES                                                                        */
/* ========================================================================================== */

#ifdef __cplusplus
extern "C" 
{
#endif

/*
    FMOD System memory functions (optional).
*/

FMOD_RESULT F_API FMOD_Memory_Initialize           (void *poolmem, int poollen, FMOD_MEMORY_ALLOCCALLBACK useralloc, FMOD_MEMORY_REALLOCCALLBACK userrealloc, FMOD_MEMORY_FREECALLBACK userfree);
FMOD_RESULT F_API FMOD_Memory_GetStats             (int *currentalloced, int *maxalloced);

/*
    FMOD System factory functions.  Use this to create an FMOD System Instance.  below you will see FMOD_System_Init/Close to get started.
*/

FMOD_RESULT F_API FMOD_System_Create               (FMOD_SYSTEM **system); 
FMOD_RESULT F_API FMOD_System_Release              (FMOD_SYSTEM *system); 


/*
    'System' API
*/

/*
     Pre-init functions.
*/

FMOD_RESULT F_API FMOD_System_SetOutput              (FMOD_SYSTEM *system, FMOD_OUTPUTTYPE output);
FMOD_RESULT F_API FMOD_System_GetOutput              (FMOD_SYSTEM *system, FMOD_OUTPUTTYPE *output);
FMOD_RESULT F_API FMOD_System_GetNumDrivers          (FMOD_SYSTEM *system, int *numdrivers);
FMOD_RESULT F_API FMOD_System_GetDriverName          (FMOD_SYSTEM *system, int id, char *name, int namelen);
FMOD_RESULT F_API FMOD_System_GetDriverCaps          (FMOD_SYSTEM *system, int id, FMOD_CAPS *caps, int *minfrequency, int *maxfrequency, FMOD_SPEAKERMODE *controlpanelspeakermode);
FMOD_RESULT F_API FMOD_System_SetDriver              (FMOD_SYSTEM *system, int driver);
FMOD_RESULT F_API FMOD_System_GetDriver              (FMOD_SYSTEM *system, int *driver);
FMOD_RESULT F_API FMOD_System_SetHardwareChannels    (FMOD_SYSTEM *system, int min2d, int max2d, int min3d, int max3d);
FMOD_RESULT F_API FMOD_System_GetHardwareChannels    (FMOD_SYSTEM *system, int *num2d, int *num3d, int *total);
FMOD_RESULT F_API FMOD_System_SetSoftwareChannels    (FMOD_SYSTEM *system, int numsoftwarechannels);
FMOD_RESULT F_API FMOD_System_GetSoftwareChannels    (FMOD_SYSTEM *system, int *numsoftwarechannels);
FMOD_RESULT F_API FMOD_System_SetSoftwareFormat      (FMOD_SYSTEM *system, int samplerate, FMOD_SOUND_FORMAT format, int numoutputchannels, int maxinputchannels, FMOD_DSP_RESAMPLER resamplemethod);
FMOD_RESULT F_API FMOD_System_GetSoftwareFormat      (FMOD_SYSTEM *system, int *samplerate, FMOD_SOUND_FORMAT *format, int *numoutputchannels, int *maxinputchannels, FMOD_DSP_RESAMPLER *resamplemethod, int *bits);
FMOD_RESULT F_API FMOD_System_SetDSPBufferSize       (FMOD_SYSTEM *system, unsigned int bufferlength, int numbuffers);
FMOD_RESULT F_API FMOD_System_GetDSPBufferSize       (FMOD_SYSTEM *system, unsigned int *bufferlength, int *numbuffers);
FMOD_RESULT F_API FMOD_System_SetFileSystem          (FMOD_SYSTEM *system, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek, int blocksize);
FMOD_RESULT F_API FMOD_System_AttachFileSystem       (FMOD_SYSTEM *system, FMOD_FILE_OPENCALLBACK useropen, FMOD_FILE_CLOSECALLBACK userclose, FMOD_FILE_READCALLBACK userread, FMOD_FILE_SEEKCALLBACK userseek);
FMOD_RESULT F_API FMOD_System_SetAdvancedSettings    (FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT F_API FMOD_System_GetAdvancedSettings    (FMOD_SYSTEM *system, FMOD_ADVANCEDSETTINGS *settings);
FMOD_RESULT F_API FMOD_System_SetSpeakerMode         (FMOD_SYSTEM *system, FMOD_SPEAKERMODE speakermode);
FMOD_RESULT F_API FMOD_System_GetSpeakerMode         (FMOD_SYSTEM *system, FMOD_SPEAKERMODE *speakermode);

/*
     Plug-in support                       
*/

FMOD_RESULT F_API FMOD_System_SetPluginPath          (FMOD_SYSTEM *system, const char *path);
FMOD_RESULT F_API FMOD_System_LoadPlugin             (FMOD_SYSTEM *system, const char *filename, FMOD_PLUGINTYPE *plugintype, int *index);
FMOD_RESULT F_API FMOD_System_GetNumPlugins          (FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int *numplugins);
FMOD_RESULT F_API FMOD_System_GetPluginInfo          (FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int index, char *name, int namelen, unsigned int *version);
FMOD_RESULT F_API FMOD_System_UnloadPlugin           (FMOD_SYSTEM *system, FMOD_PLUGINTYPE plugintype, int index);
FMOD_RESULT F_API FMOD_System_SetOutputByPlugin      (FMOD_SYSTEM *system, int index);
FMOD_RESULT F_API FMOD_System_GetOutputByPlugin      (FMOD_SYSTEM *system, int *index);
FMOD_RESULT F_API FMOD_System_CreateCodec            (FMOD_SYSTEM *system, FMOD_CODEC_DESCRIPTION *description);

/*
     Init/Close                            
*/

FMOD_RESULT F_API FMOD_System_Init                   (FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
FMOD_RESULT F_API FMOD_System_Close                  (FMOD_SYSTEM *system);

/*
     General post-init system functions    
*/

FMOD_RESULT F_API FMOD_System_Update                 (FMOD_SYSTEM *system);

FMOD_RESULT F_API FMOD_System_Set3DSettings          (FMOD_SYSTEM *system, float dopplerscale, float distancefactor, float rolloffscale);
FMOD_RESULT F_API FMOD_System_Get3DSettings          (FMOD_SYSTEM *system, float *dopplerscale, float *distancefactor, float *rolloffscale);
FMOD_RESULT F_API FMOD_System_Set3DNumListeners      (FMOD_SYSTEM *system, int numlisteners);
FMOD_RESULT F_API FMOD_System_Get3DNumListeners      (FMOD_SYSTEM *system, int *numlisteners);
FMOD_RESULT F_API FMOD_System_Set3DListenerAttributes(FMOD_SYSTEM *system, int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_System_Get3DListenerAttributes(FMOD_SYSTEM *system, int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up);

FMOD_RESULT F_API FMOD_System_SetSpeakerPosition     (FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float x, float y);
FMOD_RESULT F_API FMOD_System_GetSpeakerPosition     (FMOD_SYSTEM *system, FMOD_SPEAKER speaker, float *x, float *y);
FMOD_RESULT F_API FMOD_System_SetStreamBufferSize    (FMOD_SYSTEM *system, unsigned int filebuffersize, FMOD_TIMEUNIT filebuffersizetype);
FMOD_RESULT F_API FMOD_System_GetStreamBufferSize    (FMOD_SYSTEM *system, unsigned int *filebuffersize, FMOD_TIMEUNIT *filebuffersizetype);

/*
     System information functions.        
*/

FMOD_RESULT F_API FMOD_System_GetVersion             (FMOD_SYSTEM *system, unsigned int *version);
FMOD_RESULT F_API FMOD_System_GetOutputHandle        (FMOD_SYSTEM *system, void **handle);
FMOD_RESULT F_API FMOD_System_GetChannelsPlaying     (FMOD_SYSTEM *system, int *channels);
FMOD_RESULT F_API FMOD_System_GetCPUUsage            (FMOD_SYSTEM *system, float *dsp, float *stream, float *update, float *total);
FMOD_RESULT F_API FMOD_System_GetSoundRAM            (FMOD_SYSTEM *system, int *currentalloced, int *maxalloced, int *total);
FMOD_RESULT F_API FMOD_System_GetNumCDROMDrives      (FMOD_SYSTEM *system, int *numdrives);
FMOD_RESULT F_API FMOD_System_GetCDROMDriveName      (FMOD_SYSTEM *system, int drive, char *drivename, int drivenamelen, char *scsiname, int scsinamelen, char *devicename, int devicenamelen);
FMOD_RESULT F_API FMOD_System_GetSpectrum            (FMOD_SYSTEM *system, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT F_API FMOD_System_GetWaveData            (FMOD_SYSTEM *system, float *wavearray, int numvalues, int channeloffset);

/*
     Sound/DSP/Channel/FX creation and retrieval.       
*/

FMOD_RESULT F_API FMOD_System_CreateSound            (FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_System_CreateStream           (FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_System_CreateDSP              (FMOD_SYSTEM *system, FMOD_DSP_DESCRIPTION *description, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_CreateDSPByType        (FMOD_SYSTEM *system, FMOD_DSP_TYPE type, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_CreateDSPByIndex       (FMOD_SYSTEM *system, int index, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_CreateChannelGroup     (FMOD_SYSTEM *system, const char *name, FMOD_CHANNELGROUP **channelgroup);

FMOD_RESULT F_API FMOD_System_PlaySound              (FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_System_PlayDSP                (FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_DSP *dsp, FMOD_BOOL paused, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_System_GetChannel             (FMOD_SYSTEM *system, int channelid, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_System_GetMasterChannelGroup  (FMOD_SYSTEM *system, FMOD_CHANNELGROUP **channelgroup);

/*
     Reverb API                           
*/

FMOD_RESULT F_API FMOD_System_SetReverbProperties    (FMOD_SYSTEM *system, const FMOD_REVERB_PROPERTIES *prop);
FMOD_RESULT F_API FMOD_System_GetReverbProperties    (FMOD_SYSTEM *system, FMOD_REVERB_PROPERTIES *prop);

/*
     System level DSP access.
*/

FMOD_RESULT F_API FMOD_System_GetDSPHead             (FMOD_SYSTEM *system, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_System_AddDSP                 (FMOD_SYSTEM *system, FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_System_LockDSP                (FMOD_SYSTEM *system);
FMOD_RESULT F_API FMOD_System_UnlockDSP              (FMOD_SYSTEM *system);

/*
     Recording API.
*/

FMOD_RESULT F_API FMOD_System_SetRecordDriver        (FMOD_SYSTEM *system, int driver);
FMOD_RESULT F_API FMOD_System_GetRecordDriver        (FMOD_SYSTEM *system, int *driver);
FMOD_RESULT F_API FMOD_System_GetRecordNumDrivers    (FMOD_SYSTEM *system, int *numdrivers);
FMOD_RESULT F_API FMOD_System_GetRecordDriverName    (FMOD_SYSTEM *system, int id, char *name, int namelen);
FMOD_RESULT F_API FMOD_System_GetRecordPosition      (FMOD_SYSTEM *system, unsigned int *position);

FMOD_RESULT F_API FMOD_System_RecordStart            (FMOD_SYSTEM *system, FMOD_SOUND *sound, FMOD_BOOL loop);
FMOD_RESULT F_API FMOD_System_RecordStop             (FMOD_SYSTEM *system);
FMOD_RESULT F_API FMOD_System_IsRecording            (FMOD_SYSTEM *system, FMOD_BOOL *recording);

/*
     Geometry API.
*/

FMOD_RESULT F_API FMOD_System_CreateGeometry         (FMOD_SYSTEM *system, int maxpolygons, int maxvertices, FMOD_GEOMETRY **geometry);
FMOD_RESULT F_API FMOD_System_SetGeometrySettings    (FMOD_SYSTEM *system, float maxworldsize);
FMOD_RESULT F_API FMOD_System_GetGeometrySettings    (FMOD_SYSTEM *system, float *maxworldsize);
FMOD_RESULT F_API FMOD_System_LoadGeometry           (FMOD_SYSTEM *system, const void *data, int datasize, FMOD_GEOMETRY **geometry);

/*
     Network functions.
*/

FMOD_RESULT F_API FMOD_System_SetNetworkProxy        (FMOD_SYSTEM *system, const char *proxy);
FMOD_RESULT F_API FMOD_System_GetNetworkProxy        (FMOD_SYSTEM *system, char *proxy, int proxylen);
FMOD_RESULT F_API FMOD_System_SetNetworkTimeout      (FMOD_SYSTEM *system, int timeout);
FMOD_RESULT F_API FMOD_System_GetNetworkTimeout      (FMOD_SYSTEM *system, int *timeout);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_System_SetUserData            (FMOD_SYSTEM *system, void *userdata);
FMOD_RESULT F_API FMOD_System_GetUserData            (FMOD_SYSTEM *system, void **userdata);

/*
    'Sound' API
*/

FMOD_RESULT F_API FMOD_Sound_Release                 (FMOD_SOUND *sound);
FMOD_RESULT F_API FMOD_Sound_GetSystemObject         (FMOD_SOUND *sound, FMOD_SYSTEM **system);

/*
     Standard sound manipulation functions.                                                
*/

FMOD_RESULT F_API FMOD_Sound_Lock                    (FMOD_SOUND *sound, unsigned int offset, unsigned int length, void **ptr1, void **ptr2, unsigned int *len1, unsigned int *len2);
FMOD_RESULT F_API FMOD_Sound_Unlock                  (FMOD_SOUND *sound, void *ptr1, void *ptr2, unsigned int len1, unsigned int len2);
FMOD_RESULT F_API FMOD_Sound_SetDefaults             (FMOD_SOUND *sound, float frequency, float volume, float pan, int priority);
FMOD_RESULT F_API FMOD_Sound_GetDefaults             (FMOD_SOUND *sound, float *frequency, float *volume, float *pan, int *priority);
FMOD_RESULT F_API FMOD_Sound_SetVariations           (FMOD_SOUND *sound, float frequencyvar, float volumevar, float panvar);
FMOD_RESULT F_API FMOD_Sound_GetVariations           (FMOD_SOUND *sound, float *frequencyvar, float *volumevar, float *panvar);
FMOD_RESULT F_API FMOD_Sound_Set3DMinMaxDistance     (FMOD_SOUND *sound, float min, float max);
FMOD_RESULT F_API FMOD_Sound_Get3DMinMaxDistance     (FMOD_SOUND *sound, float *min, float *max);
FMOD_RESULT F_API FMOD_Sound_Set3DConeSettings       (FMOD_SOUND *sound, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT F_API FMOD_Sound_Get3DConeSettings       (FMOD_SOUND *sound, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT F_API FMOD_Sound_Set3DCustomRolloff      (FMOD_SOUND *sound, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT F_API FMOD_Sound_Get3DCustomRolloff      (FMOD_SOUND *sound, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT F_API FMOD_Sound_SetSubSound             (FMOD_SOUND *sound, int index, FMOD_SOUND *subsound);
FMOD_RESULT F_API FMOD_Sound_GetSubSound             (FMOD_SOUND *sound, int index, FMOD_SOUND **subsound);
FMOD_RESULT F_API FMOD_Sound_SetSubSoundSentence     (FMOD_SOUND *sound, int *subsoundlist, int numsubsounds);
FMOD_RESULT F_API FMOD_Sound_GetName                 (FMOD_SOUND *sound, char *name, int namelen);
FMOD_RESULT F_API FMOD_Sound_GetLength               (FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype);
FMOD_RESULT F_API FMOD_Sound_GetFormat               (FMOD_SOUND *sound, FMOD_SOUND_TYPE *type, FMOD_SOUND_FORMAT *format, int *channels, int *bits);
FMOD_RESULT F_API FMOD_Sound_GetNumSubSounds         (FMOD_SOUND *sound, int *numsubsounds);
FMOD_RESULT F_API FMOD_Sound_GetNumTags              (FMOD_SOUND *sound, int *numtags, int *numtagsupdated);
FMOD_RESULT F_API FMOD_Sound_GetTag                  (FMOD_SOUND *sound, const char *name, int index, FMOD_TAG *tag);
FMOD_RESULT F_API FMOD_Sound_GetOpenState            (FMOD_SOUND *sound, FMOD_OPENSTATE *openstate, unsigned int *percentbuffered, FMOD_BOOL *starving);
FMOD_RESULT F_API FMOD_Sound_ReadData                (FMOD_SOUND *sound, void *buffer, unsigned int lenbytes, unsigned int *read);
FMOD_RESULT F_API FMOD_Sound_SeekData                (FMOD_SOUND *sound, unsigned int pcm);

/*
     Synchronization point API.  These points can come from markers embedded in wav files, and can also generate channel callbacks.        
*/

FMOD_RESULT F_API FMOD_Sound_GetNumSyncPoints        (FMOD_SOUND *sound, int *numsyncpoints);
FMOD_RESULT F_API FMOD_Sound_GetSyncPoint            (FMOD_SOUND *sound, int index, FMOD_SYNCPOINT **point);
FMOD_RESULT F_API FMOD_Sound_GetSyncPointInfo        (FMOD_SOUND *sound, FMOD_SYNCPOINT *point, char *name, int namelen, unsigned int *offset, FMOD_TIMEUNIT offsettype);
FMOD_RESULT F_API FMOD_Sound_AddSyncPoint            (FMOD_SOUND *sound, unsigned int offset, FMOD_TIMEUNIT offsettype, const char *name, FMOD_SYNCPOINT **point);
FMOD_RESULT F_API FMOD_Sound_DeleteSyncPoint         (FMOD_SOUND *sound, FMOD_SYNCPOINT *point);

/*
     Functions also in Channel class but here they are the 'default' to save having to change it in Channel all the time.
*/

FMOD_RESULT F_API FMOD_Sound_SetMode                 (FMOD_SOUND *sound, FMOD_MODE mode);
FMOD_RESULT F_API FMOD_Sound_GetMode                 (FMOD_SOUND *sound, FMOD_MODE *mode);
FMOD_RESULT F_API FMOD_Sound_SetLoopCount            (FMOD_SOUND *sound, int loopcount);
FMOD_RESULT F_API FMOD_Sound_GetLoopCount            (FMOD_SOUND *sound, int *loopcount);
FMOD_RESULT F_API FMOD_Sound_SetLoopPoints           (FMOD_SOUND *sound, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT F_API FMOD_Sound_GetLoopPoints           (FMOD_SOUND *sound, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_Sound_SetUserData             (FMOD_SOUND *sound, void *userdata);
FMOD_RESULT F_API FMOD_Sound_GetUserData             (FMOD_SOUND *sound, void **userdata);

/*
    'Channel' API
*/

FMOD_RESULT F_API FMOD_Channel_GetSystemObject       (FMOD_CHANNEL *channel, FMOD_SYSTEM **system);

FMOD_RESULT F_API FMOD_Channel_Stop                  (FMOD_CHANNEL *channel);
FMOD_RESULT F_API FMOD_Channel_SetPaused             (FMOD_CHANNEL *channel, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_Channel_GetPaused             (FMOD_CHANNEL *channel, FMOD_BOOL *paused);
FMOD_RESULT F_API FMOD_Channel_SetVolume             (FMOD_CHANNEL *channel, float volume);
FMOD_RESULT F_API FMOD_Channel_GetVolume             (FMOD_CHANNEL *channel, float *volume);
FMOD_RESULT F_API FMOD_Channel_SetFrequency          (FMOD_CHANNEL *channel, float frequency);
FMOD_RESULT F_API FMOD_Channel_GetFrequency          (FMOD_CHANNEL *channel, float *frequency);
FMOD_RESULT F_API FMOD_Channel_SetPan                (FMOD_CHANNEL *channel, float pan);
FMOD_RESULT F_API FMOD_Channel_GetPan                (FMOD_CHANNEL *channel, float *pan);
FMOD_RESULT F_API FMOD_Channel_SetDelay              (FMOD_CHANNEL *channel, unsigned int startdelay, unsigned int enddelay);
FMOD_RESULT F_API FMOD_Channel_GetDelay              (FMOD_CHANNEL *channel, unsigned int *startdelay, unsigned int *enddelay);
FMOD_RESULT F_API FMOD_Channel_SetSpeakerMix         (FMOD_CHANNEL *channel, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);
FMOD_RESULT F_API FMOD_Channel_GetSpeakerMix         (FMOD_CHANNEL *channel, float *frontleft, float *frontright, float *center, float *lfe, float *backleft, float *backright, float *sideleft, float *sideright);
FMOD_RESULT F_API FMOD_Channel_SetSpeakerLevels      (FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_Channel_GetSpeakerLevels      (FMOD_CHANNEL *channel, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_Channel_SetMute               (FMOD_CHANNEL *channel, FMOD_BOOL mute);
FMOD_RESULT F_API FMOD_Channel_GetMute               (FMOD_CHANNEL *channel, FMOD_BOOL *mute);
FMOD_RESULT F_API FMOD_Channel_SetPriority           (FMOD_CHANNEL *channel, int priority);
FMOD_RESULT F_API FMOD_Channel_GetPriority           (FMOD_CHANNEL *channel, int *priority);
FMOD_RESULT F_API FMOD_Channel_SetPosition           (FMOD_CHANNEL *channel, unsigned int position, FMOD_TIMEUNIT postype);
FMOD_RESULT F_API FMOD_Channel_GetPosition           (FMOD_CHANNEL *channel, unsigned int *position, FMOD_TIMEUNIT postype);
FMOD_RESULT F_API FMOD_Channel_SetReverbProperties   (FMOD_CHANNEL *channel, const FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT F_API FMOD_Channel_GetReverbProperties   (FMOD_CHANNEL *channel, FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT F_API FMOD_Channel_SetChannelGroup       (FMOD_CHANNEL *channel, FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT F_API FMOD_Channel_GetChannelGroup       (FMOD_CHANNEL *channel, FMOD_CHANNELGROUP **channelgroup);
FMOD_RESULT F_API FMOD_Channel_SetCallback           (FMOD_CHANNEL *channel, FMOD_CHANNEL_CALLBACKTYPE type, FMOD_CHANNEL_CALLBACK callback, int command);

/*
     3D functionality.
*/

FMOD_RESULT F_API FMOD_Channel_Set3DAttributes       (FMOD_CHANNEL *channel, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_Channel_Get3DAttributes       (FMOD_CHANNEL *channel, FMOD_VECTOR *pos, FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_Channel_Set3DMinMaxDistance   (FMOD_CHANNEL *channel, float mindistance, float maxdistance);
FMOD_RESULT F_API FMOD_Channel_Get3DMinMaxDistance   (FMOD_CHANNEL *channel, float *mindistance, float *maxdistance);
FMOD_RESULT F_API FMOD_Channel_Set3DConeSettings     (FMOD_CHANNEL *channel, float insideconeangle, float outsideconeangle, float outsidevolume);
FMOD_RESULT F_API FMOD_Channel_Get3DConeSettings     (FMOD_CHANNEL *channel, float *insideconeangle, float *outsideconeangle, float *outsidevolume);
FMOD_RESULT F_API FMOD_Channel_Set3DConeOrientation  (FMOD_CHANNEL *channel, FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_Channel_Get3DConeOrientation  (FMOD_CHANNEL *channel, FMOD_VECTOR *orientation);
FMOD_RESULT F_API FMOD_Channel_Set3DCustomRolloff    (FMOD_CHANNEL *channel, FMOD_VECTOR *points, int numpoints);
FMOD_RESULT F_API FMOD_Channel_Get3DCustomRolloff    (FMOD_CHANNEL *channel, FMOD_VECTOR **points, int *numpoints);
FMOD_RESULT F_API FMOD_Channel_Set3DOcclusion        (FMOD_CHANNEL *channel, float directocclusion, float reverbocclusion);
FMOD_RESULT F_API FMOD_Channel_Get3DOcclusion        (FMOD_CHANNEL *channel, float *directocclusion, float *reverbocclusion);
FMOD_RESULT F_API FMOD_Channel_Set3DSpread           (FMOD_CHANNEL *channel, float angle);
FMOD_RESULT F_API FMOD_Channel_Get3DSpread           (FMOD_CHANNEL *channel, float *angle);

/*
     DSP functionality only for channels playing sounds created with FMOD_SOFTWARE.
*/

FMOD_RESULT F_API FMOD_Channel_GetDSPHead            (FMOD_CHANNEL *channel, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_Channel_AddDSP                (FMOD_CHANNEL *channel, FMOD_DSP *dsp);

/*
     Information only functions.
*/

FMOD_RESULT F_API FMOD_Channel_IsPlaying             (FMOD_CHANNEL *channel, FMOD_BOOL *isplaying);
FMOD_RESULT F_API FMOD_Channel_IsVirtual             (FMOD_CHANNEL *channel, FMOD_BOOL *isvirtual);
FMOD_RESULT F_API FMOD_Channel_GetAudibility         (FMOD_CHANNEL *channel, float *audibility);
FMOD_RESULT F_API FMOD_Channel_GetCurrentSound       (FMOD_CHANNEL *channel, FMOD_SOUND **sound);
FMOD_RESULT F_API FMOD_Channel_GetSpectrum           (FMOD_CHANNEL *channel, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT F_API FMOD_Channel_GetWaveData           (FMOD_CHANNEL *channel, float *wavearray, int numvalues, int channeloffset);
FMOD_RESULT F_API FMOD_Channel_GetIndex              (FMOD_CHANNEL *channel, int *index);

/*
     Functions also found in Sound class but here they can be set per channel.
*/

FMOD_RESULT F_API FMOD_Channel_SetMode               (FMOD_CHANNEL *channel, FMOD_MODE mode);
FMOD_RESULT F_API FMOD_Channel_GetMode               (FMOD_CHANNEL *channel, FMOD_MODE *mode);
FMOD_RESULT F_API FMOD_Channel_SetLoopCount          (FMOD_CHANNEL *channel, int loopcount);
FMOD_RESULT F_API FMOD_Channel_GetLoopCount          (FMOD_CHANNEL *channel, int *loopcount);
FMOD_RESULT F_API FMOD_Channel_SetLoopPoints         (FMOD_CHANNEL *channel, unsigned int loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int loopend, FMOD_TIMEUNIT loopendtype);
FMOD_RESULT F_API FMOD_Channel_GetLoopPoints         (FMOD_CHANNEL *channel, unsigned int *loopstart, FMOD_TIMEUNIT loopstarttype, unsigned int *loopend, FMOD_TIMEUNIT loopendtype);

/*
     Userdata set/get.                                                
*/

FMOD_RESULT F_API FMOD_Channel_SetUserData           (FMOD_CHANNEL *channel, void *userdata);
FMOD_RESULT F_API FMOD_Channel_GetUserData           (FMOD_CHANNEL *channel, void **userdata);

/*
    'ChannelGroup' API
*/

FMOD_RESULT F_API FMOD_ChannelGroup_Release          (FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT F_API FMOD_ChannelGroup_GetSystemObject  (FMOD_CHANNELGROUP *channelgroup, FMOD_SYSTEM **system);

/*
     Channelgroup scale values.  (changes attributes relative to the channels, doesn't overwrite them)
*/

FMOD_RESULT F_API FMOD_ChannelGroup_SetVolume        (FMOD_CHANNELGROUP *channelgroup, float volume);
FMOD_RESULT F_API FMOD_ChannelGroup_GetVolume        (FMOD_CHANNELGROUP *channelgroup, float *volume);
FMOD_RESULT F_API FMOD_ChannelGroup_SetPitch         (FMOD_CHANNELGROUP *channelgroup, float pitch);
FMOD_RESULT F_API FMOD_ChannelGroup_GetPitch         (FMOD_CHANNELGROUP *channelgroup, float *pitch);

/*
     Channelgroup override values.  (recursively overwrites whatever settings the channels had)
*/

FMOD_RESULT F_API FMOD_ChannelGroup_Stop             (FMOD_CHANNELGROUP *channelgroup);
FMOD_RESULT F_API FMOD_ChannelGroup_OverridePaused   (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL paused);
FMOD_RESULT F_API FMOD_ChannelGroup_OverrideVolume   (FMOD_CHANNELGROUP *channelgroup, float volume);
FMOD_RESULT F_API FMOD_ChannelGroup_OverrideFrequency(FMOD_CHANNELGROUP *channelgroup, float frequency);
FMOD_RESULT F_API FMOD_ChannelGroup_OverridePan      (FMOD_CHANNELGROUP *channelgroup, float pan);
FMOD_RESULT F_API FMOD_ChannelGroup_OverrideMute     (FMOD_CHANNELGROUP *channelgroup, FMOD_BOOL mute);
FMOD_RESULT F_API FMOD_ChannelGroup_OverrideReverbProperties(FMOD_CHANNELGROUP *channelgroup, const FMOD_REVERB_CHANNELPROPERTIES *prop);
FMOD_RESULT F_API FMOD_ChannelGroup_Override3DAttributes(FMOD_CHANNELGROUP *channelgroup, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel);
FMOD_RESULT F_API FMOD_ChannelGroup_OverrideSpeakerMix(FMOD_CHANNELGROUP *channelgroup, float frontleft, float frontright, float center, float lfe, float backleft, float backright, float sideleft, float sideright);

/*
     Nested channel groups.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_AddGroup         (FMOD_CHANNELGROUP *channelgroup, FMOD_CHANNELGROUP *group);
FMOD_RESULT F_API FMOD_ChannelGroup_GetNumGroups     (FMOD_CHANNELGROUP *channelgroup, int *numgroups);
FMOD_RESULT F_API FMOD_ChannelGroup_GetGroup         (FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNELGROUP **group);

/*
     DSP functionality only for channel groups playing sounds created with FMOD_SOFTWARE.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_GetDSPHead       (FMOD_CHANNELGROUP *channelgroup, FMOD_DSP **dsp);
FMOD_RESULT F_API FMOD_ChannelGroup_AddDSP           (FMOD_CHANNELGROUP *channelgroup, FMOD_DSP *dsp);

/*
     Information only functions.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_GetName          (FMOD_CHANNELGROUP *channelgroup, char *name, int namelen);
FMOD_RESULT F_API FMOD_ChannelGroup_GetNumChannels   (FMOD_CHANNELGROUP *channelgroup, int *numchannels);
FMOD_RESULT F_API FMOD_ChannelGroup_GetChannel       (FMOD_CHANNELGROUP *channelgroup, int index, FMOD_CHANNEL **channel);
FMOD_RESULT F_API FMOD_ChannelGroup_GetSpectrum      (FMOD_CHANNELGROUP *channelgroup, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);
FMOD_RESULT F_API FMOD_ChannelGroup_GetWaveData      (FMOD_CHANNELGROUP *channelgroup, float *wavearray, int numvalues, int channeloffset);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_ChannelGroup_SetUserData      (FMOD_CHANNELGROUP *channelgroup, void *userdata);
FMOD_RESULT F_API FMOD_ChannelGroup_GetUserData      (FMOD_CHANNELGROUP *channelgroup, void **userdata);

/*
    'DSP' API
*/

FMOD_RESULT F_API FMOD_DSP_Release                   (FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_DSP_GetSystemObject           (FMOD_DSP *dsp, FMOD_SYSTEM **system);

/*
     Connection / disconnection / input and output enumeration.
*/

FMOD_RESULT F_API FMOD_DSP_AddInput                  (FMOD_DSP *dsp, FMOD_DSP *input);
FMOD_RESULT F_API FMOD_DSP_DisconnectFrom            (FMOD_DSP *dsp, FMOD_DSP *target);
FMOD_RESULT F_API FMOD_DSP_Remove                    (FMOD_DSP *dsp);
FMOD_RESULT F_API FMOD_DSP_GetNumInputs              (FMOD_DSP *dsp, int *numinputs);
FMOD_RESULT F_API FMOD_DSP_GetNumOutputs             (FMOD_DSP *dsp, int *numoutputs);
FMOD_RESULT F_API FMOD_DSP_GetInput                  (FMOD_DSP *dsp, int index, FMOD_DSP **input);
FMOD_RESULT F_API FMOD_DSP_GetOutput                 (FMOD_DSP *dsp, int index, FMOD_DSP **output);
FMOD_RESULT F_API FMOD_DSP_SetInputMix               (FMOD_DSP *dsp, int index, float volume);
FMOD_RESULT F_API FMOD_DSP_GetInputMix               (FMOD_DSP *dsp, int index, float *volume);
FMOD_RESULT F_API FMOD_DSP_SetInputLevels            (FMOD_DSP *dsp, int index, FMOD_SPEAKER speaker, float *levels, int numlevels);
FMOD_RESULT F_API FMOD_DSP_GetInputLevels            (FMOD_DSP *dsp, int index, FMOD_SPEAKER speaker, float *levels, int numlevels);

/*
     DSP unit control.
*/

FMOD_RESULT F_API FMOD_DSP_SetActive                 (FMOD_DSP *dsp, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_DSP_GetActive                 (FMOD_DSP *dsp, FMOD_BOOL *active);
FMOD_RESULT F_API FMOD_DSP_SetBypass                 (FMOD_DSP *dsp, FMOD_BOOL bypass);
FMOD_RESULT F_API FMOD_DSP_GetBypass                 (FMOD_DSP *dsp, FMOD_BOOL *bypass);
FMOD_RESULT F_API FMOD_DSP_Reset                     (FMOD_DSP *dsp);

/*
     DSP parameter control.
*/

FMOD_RESULT F_API FMOD_DSP_SetParameter              (FMOD_DSP *dsp, int index, float value);
FMOD_RESULT F_API FMOD_DSP_GetParameter              (FMOD_DSP *dsp, int index, float *value, char *valuestr, int valuestrlen);
FMOD_RESULT F_API FMOD_DSP_GetNumParameters          (FMOD_DSP *dsp, int *numparams);
FMOD_RESULT F_API FMOD_DSP_GetParameterInfo          (FMOD_DSP *dsp, int index, char *name, char *label, char *description, int descriptionlen, float *min, float *max);
FMOD_RESULT F_API FMOD_DSP_ShowConfigDialog          (FMOD_DSP *dsp, void *hwnd, FMOD_BOOL show);

/*
     DSP attributes.        
*/

FMOD_RESULT F_API FMOD_DSP_GetInfo                   (FMOD_DSP *dsp, char *name, unsigned int *version, int *channels, int *configwidth, int *configheight);
FMOD_RESULT F_API FMOD_DSP_SetDefaults               (FMOD_DSP *dsp, float frequency, float volume, float pan, int priority);
FMOD_RESULT F_API FMOD_DSP_GetDefaults               (FMOD_DSP *dsp, float *frequency, float *volume, float *pan, int *priority);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_DSP_SetUserData               (FMOD_DSP *dsp, void *userdata);
FMOD_RESULT F_API FMOD_DSP_GetUserData               (FMOD_DSP *dsp, void **userdata);

/*
    'Geometry' API
*/

FMOD_RESULT F_API FMOD_Geometry_Release              (FMOD_GEOMETRY *geometry);

FMOD_RESULT F_API FMOD_Geometry_AddPolygon           (FMOD_GEOMETRY *geometry, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided, int numvertices, const FMOD_VECTOR *vertices, int *polygonindex);
FMOD_RESULT F_API FMOD_Geometry_GetNumPolygons       (FMOD_GEOMETRY *geometry, int *numpolygons);
FMOD_RESULT F_API FMOD_Geometry_GetMaxPolygons       (FMOD_GEOMETRY *geometry, int *maxpolygons, int *maxvertices);
FMOD_RESULT F_API FMOD_Geometry_GetPolygonNumVertices(FMOD_GEOMETRY *geometry, int index, int *numvertices);
FMOD_RESULT F_API FMOD_Geometry_SetPolygonVertex     (FMOD_GEOMETRY *geometry, int index, int vertexindex, const FMOD_VECTOR *vertex);
FMOD_RESULT F_API FMOD_Geometry_GetPolygonVertex     (FMOD_GEOMETRY *geometry, int index, int vertexindex, FMOD_VECTOR *vertex);
FMOD_RESULT F_API FMOD_Geometry_SetPolygonAttributes (FMOD_GEOMETRY *geometry, int index, float directocclusion, float reverbocclusion, FMOD_BOOL doublesided);
FMOD_RESULT F_API FMOD_Geometry_GetPolygonAttributes (FMOD_GEOMETRY *geometry, int index, float *directocclusion, float *reverbocclusion, FMOD_BOOL *doublesided);

FMOD_RESULT F_API FMOD_Geometry_SetActive            (FMOD_GEOMETRY *geometry, FMOD_BOOL active);
FMOD_RESULT F_API FMOD_Geometry_GetActive            (FMOD_GEOMETRY *geometry, FMOD_BOOL *active);
FMOD_RESULT F_API FMOD_Geometry_SetRotation          (FMOD_GEOMETRY *geometry, const FMOD_VECTOR *forward, const FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_Geometry_GetRotation          (FMOD_GEOMETRY *geometry, FMOD_VECTOR *forward, FMOD_VECTOR *up);
FMOD_RESULT F_API FMOD_Geometry_SetPosition          (FMOD_GEOMETRY *geometry, const FMOD_VECTOR *position);
FMOD_RESULT F_API FMOD_Geometry_GetPosition          (FMOD_GEOMETRY *geometry, FMOD_VECTOR *position);
FMOD_RESULT F_API FMOD_Geometry_SetScale             (FMOD_GEOMETRY *geometry, const FMOD_VECTOR *scale);
FMOD_RESULT F_API FMOD_Geometry_GetScale             (FMOD_GEOMETRY *geometry, FMOD_VECTOR *scale);
FMOD_RESULT F_API FMOD_Geometry_Save                 (FMOD_GEOMETRY *geometry, void *data, int *datasize);

/*
     Userdata set/get.
*/

FMOD_RESULT F_API FMOD_Geometry_SetUserData          (FMOD_GEOMETRY *geometry, void *userdata);
FMOD_RESULT F_API FMOD_Geometry_GetUserData          (FMOD_GEOMETRY *geometry, void **userdata);

#ifdef __cplusplus
}
#endif

#endif

