//
//  HCacheValue.h
//  HCacheiOS
//
//  Created by mac studio on 2022/8/13.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, HCacheValueType) {
    HCacheValueTypeNULL,
    HCacheValueTypeInt,
    HCacheValueTypeLong,
    HCacheValueTypeFloat,
    HCacheValueTypeDouble,
    HCacheValueTypeString,
    HCacheValueTypeJSONString,
    HCacheValueTypeBOOL
};

NS_ASSUME_NONNULL_BEGIN

@interface HCacheValue : NSObject

@property (nonatomic, assign, readonly) HCacheValueType type;
@property (nonatomic, strong, readonly) id value;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithType:(HCacheValueType)type withValue:(id)value;
+ (instancetype)cacheWithType:(HCacheValueType)type withValue:(id)value;

- (BOOL)isNull;
- (BOOL)isInt;
- (BOOL)isBOOL;
- (BOOL)isLong;
- (BOOL)isFloat;
- (BOOL)isDouble;
- (BOOL)isString;
- (BOOL)isJsonString;

- (BOOL)boolVlaue;
- (int)intValue;
- (long)longVlaue;
- (float)floatValue;
- (double)doubleValue;
- (NSString *)stringValue;
- (NSString *)jsonValue;

@end

NS_ASSUME_NONNULL_END
