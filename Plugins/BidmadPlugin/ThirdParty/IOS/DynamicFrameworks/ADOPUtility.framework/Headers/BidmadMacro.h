//
//  BidmadMacro.h
//  ADOPUtility
//
//  Created by Seungsub Oh on 2022/12/08.
//

#define bidmadWeakify(var) __weak typeof(var) bidmadWeak_##var = var;

#define bidmadStrongify(var) \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wshadow\"") \
if (bidmadWeak_##var == nil) { return; } \
__strong typeof(bidmadWeak_##var) var = bidmadWeak_##var; \
_Pragma("clang diagnostic pop")

#define BIDMAD_START_SUPPRESS_UNUSED_VAR \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wunused-variable\"")

#define BIDMAD_END_SUPPRESS_UNUSED_VAR \
_Pragma("clang diagnostic pop")

#define BIDMAD_START_ENFORCE_PROTOCOL_IMPLEMENTATION \
_Pragma("GCC diagnostic push") \
_Pragma("GCC diagnostic error \"-Wprotocol\"")

#define BIDMAD_END_ENFORCE_PROTOCOL_IMPLEMENTATION \
_Pragma("GCC diagnostic pop")

#define BIDMAD_START_SUPPRESS_SELECTOR_WARNING \
_Pragma("clang diagnostic push") \
_Pragma("clang diagnostic ignored \"-Wundeclared-selector\"")

#define BIDMAD_END_SUPPRESS_SELECTOR_WARNING \
_Pragma("clang diagnostic pop")

#define BIDMAD_CALLTOACTION_FLUTTER_VIEW_REFERENCE @"com.bidmad.sdk.nativead/CallToActionView_"
#define BIDMAD_FLUTTER_CHANNEL_PREFIX            @"com.bidmad.sdk/"
#define BIDMAD_FLUTTER_CHANNEL_NATIVE_AD_FACTORY @"com.bidmad.sdk.nativead/Widget_"
#define BIDMAD_FLUTTER_NATIVE_AD_VIEW_TYPE       @"BidmadNativeAdWidget"


#define BidmadFlutterMethodClosure \
^(id call, void (^result)(id))
