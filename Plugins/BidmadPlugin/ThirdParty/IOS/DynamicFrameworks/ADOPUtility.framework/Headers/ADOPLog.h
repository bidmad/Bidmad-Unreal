//
//  ADOPLog.h
//  ADOPUtility
//
//  Created by Seungsub Oh on 2022/08/17.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, ADOPLogLevel) {
    ADOPLogLevelInfo,
    ADOPLogLevelDev,
    ADOPLogLevelTest
};

@interface ADOPLog : NSObject

/// Function: print out console log
/// Args: LogLevel (Info, Dev, Test), Strings (Variadic)
+ (void (^)(ADOPLogLevel logLevel, NSString *methodCaller, NSString *format, va_list args))print;
+ (void (^)(NSString *, ...))printInfo;
+ (void (^)(NSString *, ...))printDev;
+ (void (^)(NSString *, ...))printTest;

@end

NS_ASSUME_NONNULL_END
