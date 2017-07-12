#include <iostream>
#include "TagBeeHD.h"
#include "Utility.h"

TagBeeHD::TagBeeHD()
{
    //ctor
    initTagSet();
}

TagBeeHD::~TagBeeHD()
{
    //dtor
}
bool TagBeeHD::isTagMatch(string tag){
    if(mTagSet->end() == mTagSet->find(Utility::splitTagColon(tag))){
        return false;
    }
    return true;
}

void TagBeeHD::initTagSet(){

    mTagSet = new TagSet();
    mTagSet->clear();

    //AP
    mTagSet->insert("InCall");
    mTagSet->insert("Telephony");
    mTagSet->insert("TPhoneUtils");
    mTagSet->insert("TPhoneService");
    mTagSet->insert("ParcelableCall");
    mTagSet->insert("TelecomFramework");
    //radvision
    mTagSet->insert("ImsCall");
    mTagSet->insert("ImsServiceSub");
    mTagSet->insert("FihImsSenderRxr");
    mTagSet->insert("ImsCallSessionImpl");
    mTagSet->insert("ImsServiceClassTracker");
    mTagSet->insert("ImsCallSessionListenerProxy");
    mTagSet->insert("VideoCall_ImsVideoCallProviderImpl");
    //JNI
    mTagSet->insert("Jni_beehd");
    //library
    mTagSet->insert("RvInternalLog");
    //application
    mTagSet->insert("GVCHandler");
    mTagSet->insert("AjantechLog");
    mTagSet->insert("CAndroidMediaDecoder");
    mTagSet->insert("PALMediaCodecsHandler");
    mTagSet->insert("PALMediaCodecsAvcDecoder");
    mTagSet->insert("com.radvision.beehd.service.AppService");
    mTagSet->insert("com.radvision.beehd.appl.BeehdServiceInt");
    mTagSet->insert("com.radvision.beehd.appl.BeehdCall");
    mTagSet->insert("com.radvision.beehd.api.RvV2oipCall");
    mTagSet->insert("com.radvision.beehd.service.CommandProcessor");
    mTagSet->insert("com.radvision.beehd.prefs.GlobalStorage");
    mTagSet->insert("com.radvision.beehd.api.RvV2oipClient");
    //Others
    mTagSet->insert("libOpenSLES");
    mTagSet->insert("ExternalDevicesManager");
    mTagSet->insert("NetworkController.MobileSignalController(1)");
}
