/****************************************************************************

 Copyright (c) 2014-2016 SDKBOX Inc

 ****************************************************************************/


#ifndef _SDKBOX_GPGAUTHENTICATIONWRAPPER_H_
#define _SDKBOX_GPGAUTHENTICATIONWRAPPER_H_

#if __cplusplus > 199711L
#include <string>
#include "GPGConstants.h"
#include "SdkboxGooglePlayWrappedObjects.h"
#include "gpg/gpg.h"
#endif

std::unique_ptr<gpg::PlatformConfiguration> CreatePlatformConfiguration( const std::string& client_id );

namespace sdkbox
{
    
    #if __cplusplus > 199711L
    #define ImportType(x) typedef gpg::x x;
    
    ImportType(Timeout);
    ImportType(DataSource);
    ImportType(Duration);
    ImportType(GameServices);
    ImportType(SnapshotConflictPolicy);
    ImportType(SnapshotMetadata);
    ImportType(SnapshotMetadataChange);
    
    class SnapshotManager;
    
	class PluginSdkboxGooglePlay
	{
	public:

	    static void init();
        
        static SnapshotManager* snapshotManager();
        
        static GameServices* gpg();
	};

    #undef ImportType
    #endif
}

#endif
