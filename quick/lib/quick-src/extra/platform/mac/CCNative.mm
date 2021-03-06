
#include <sys/sysctl.h>
#import "platform/mac/CCNativeMac.h"

#include "native/CCNative.h"
#import "platform/mac/openudid/OpenUDIDMac.h"

#import "ReachabilityIOSMac.h"

NS_CC_EXTRA_BEGIN

#pragma mark -
#pragma mark activity indicator

void Native::showActivityIndicator(void)
{
    [[NativeMac sharedInstance] showActivityIndicator];
}

void Native::hideActivityIndicator(void)
{
    [[NativeMac sharedInstance] hideActivityIndicator];
}

#pragma mark -
#pragma mark alert view

void Native::createAlert(const char* title,
                           const char* message,
                           const char* cancelButtonTitle)
{
    NSString *title_ = [NSString stringWithUTF8String:title ? title : ""];
    NSString *message_ = [NSString stringWithUTF8String:message ? message : ""];
    NSString *cancelButtonTitle_ = cancelButtonTitle ? [NSString stringWithUTF8String:cancelButtonTitle] : nil;
    [[NativeMac sharedInstance] createAlertView:title_
                                         andMessage:message_
                               andCancelButtonTitle:cancelButtonTitle_];
}

int Native::addAlertButton(const char* buttonTitle)
{
    NSString *buttonTitle_ = [NSString stringWithUTF8String:buttonTitle ? buttonTitle : "Button"];
    return (int)[[NativeMac sharedInstance] addAlertButton:buttonTitle_];
}

#if CC_LUA_ENGINE_ENABLED > 0
int Native::addAlertButtonLua(const char* buttonTitle)
{
    return addAlertButton(buttonTitle) + 1;
}
#endif

void Native::showAlert(AlertViewDelegate* delegate)
{
    [[NativeMac sharedInstance] showAlertViewWithDelegate:delegate];
}

#if CC_LUA_ENGINE_ENABLED > 0
void Native::showAlertLua(LUA_FUNCTION listener)
{
    [[NativeMac sharedInstance] showAlertViewWithLuaListener:listener];
}
#endif

void Native::cancelAlert(void)
{
    [[NativeMac sharedInstance] cancelAlertView];
}


#pragma mark -
#pragma mark misc

void Native::openURL(const char* url)
{
    if (!url) return;
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];
    [[NSWorkspace sharedWorkspace] openURL:nsurl];
}

const string Native::getInputText(const char* title, const char* message, const char* defaultValue)
{
    NSString *title_ = [NSString stringWithUTF8String:title ? title : ""];
    NSString *message_ = [NSString stringWithUTF8String:message ? message : ""];
    NSString *defaultValue_ = [NSString stringWithUTF8String:defaultValue ? defaultValue : ""];
    NSString *input = [[NativeMac sharedInstance] getInputText:title_
                                                           message:message_
                                                      defaultValue:defaultValue_];
    return string([input cStringUsingEncoding:NSUTF8StringEncoding]);
}


#pragma mark -
#pragma mark OpenUDID

const string Native::getOpenUDID(void)
{
    return string([[OpenUDIDMac value] cStringUsingEncoding:NSUTF8StringEncoding]);
}

int Native::getNetworkStatus(void)
{
    ReachabilityIOSMac *reachability = [ReachabilityIOSMac reachabilityForInternetConnection];
    [reachability startNotifier];
    
    NetworkStatus status = [reachability currentReachabilityStatus];
    
    if(status == NotReachable)
    {
        return 0;
    }
    else if (status == ReachableViaWiFi)
    {
        return 2;
    }
    else if (status == ReachableViaWWAN)
    {
        return 1;
    }
    return 0;
}

const string Native::getDeviceName(void)
{
    size_t len = 0;
    sysctlbyname("hw.model", NULL, &len, NULL, 0);
    if (len)
    {
        char* model = static_cast<char*>(malloc(len * sizeof(char)));
        sysctlbyname("hw.model", model, &len, NULL, 0);
        string modelStr(model);
        free(model);
        return modelStr;
    }

    log("Native::getDeviceName() not support on this platform.");
    return string("");
}

const string Native::getAppVersion()
{
    NSString* version = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
    return [version UTF8String];
}

const string Native::getCountryCode()
{
    NSLocale* currentLocale = [NSLocale currentLocale];
    NSString* countryCode = [currentLocale objectForKey:NSLocaleCountryCode];
    return [countryCode UTF8String];
}

const string Native::getLanguageCode()
{
    // get the current language and country config
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];
    
    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    
    return [[temp objectForKey:NSLocaleLanguageCode] UTF8String];
}

void Native::setClipboardText(const char* text)
{
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    NSString *textObj = [NSString stringWithUTF8String:text];
    NSArray *objectsToCopy = [NSArray arrayWithObject:textObj];
    
    [pasteboard writeObjects:objectsToCopy];
}

const std::string Native::getClipboardText(void)
{
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    NSDictionary *options = [NSDictionary dictionary];
    NSArray *classes = [[NSArray alloc] initWithObjects:[NSString class], nil];
    NSArray *strings = [pasteboard readObjectsForClasses:classes options:options];
    if (strings != nil) {
        NSString *text = [strings objectAtIndex:0];
        if (text) {
            return [text UTF8String];
        }
    }

    return "";
}

void Native::vibrate()
{
    log("Native::vibrate() not support on this platform.");
}

NS_CC_EXTRA_END
