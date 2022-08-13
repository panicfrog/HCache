//
//  HCacheValue.m
//  HCacheiOS
//
//  Created by mac studio on 2022/8/13.
//

#import "HCacheValue.h"

@implementation HCacheValue

- (instancetype)initWithType:(HCacheValueType)type withValue:(id)value {
    if (self = [super init]) {
        _type = type;
        _value = value;
    }
    return self;
}

+ (instancetype)cacheWithType:(HCacheValueType)type withValue:(id)value {
    return [[self alloc] initWithType:type withValue:value];
}


- (BOOL)isNSNumberValue {
    return [_value isKindOfClass:[NSNumber class]];
}

- (BOOL)isStringValue {
    return [_value isKindOfClass:[NSString class]];
}

- (BOOL)isNull {
    return _type == HCacheValueTypeNULL;
}
- (BOOL)isInt {
    return _type == HCacheValueTypeInt && [self isNSNumberValue];
}
- (BOOL)isBOOL {
    return _type == HCacheValueTypeBOOL && [self isNSNumberValue];
}
- (BOOL)isLong {
    return _type == HCacheValueTypeLong && [self isNSNumberValue];
}
- (BOOL)isFloat {
    return _type == HCacheValueTypeFloat && [self isNSNumberValue];
}
- (BOOL)isDouble {
    return _type == HCacheValueTypeDouble && [self isNSNumberValue];
}
- (BOOL)isString {
    return _type == HCacheValueTypeString && [self isStringValue];
}
- (BOOL)isJsonString {
    return _type == HCacheValueTypeJSONString && [self isStringValue];
}


- (BOOL)boolVlaue {
   return [(NSNumber *)_value boolValue];
}
- (int)intValue {
   return [(NSNumber *)_value intValue];
}
- (long)longVlaue {
    return [(NSNumber *)_value longValue];
}
- (float)floatValue {
    return [(NSNumber *)_value floatValue];
}
- (double)doubleValue {
    return [(NSNumber *)_value doubleValue];
}
- (NSString *)stringValue {
    return (NSString *)_value;
}
- (NSString *)jsonValue {
    return (NSString *)_value;
}



@end
