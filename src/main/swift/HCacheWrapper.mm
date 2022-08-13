//
//  HCacheWrapper.m
//  HCacheExample
//
//  Created by 叶永平 on 2022/8/12.
//

#import "HCacheWrapper.h"
#include "DiskStorage.hpp"
#include "KVSingleton.hpp"

@implementation HCacheWrapper {
  cache::DiskKVStorage *kv;
}

- (void)setupWithPath:(NSString *)path {
  auto& singleton = cache::KVSingleton::getInstance();
  kv = singleton.getKV([path UTF8String]);
}

- (void)setBoolValue:(BOOL)value forKey:(NSString *)key {
  kv->saveB([key UTF8String], value);
}

- (void)setIntValue:(int)value forKey:(NSString *)key {
  kv->saveI([key UTF8String], value);
}

- (void)setLongValue:(long)value forKey:(NSString *)key {
  kv->saveL([key UTF8String], value);
}

- (void)setFloatValue:(float)value forKey:(NSString *)key {
  kv->saveF([key UTF8String], value);
}

- (void)setDoubleValue:(double)value forKey:(NSString *)key {
  kv->saveD([key UTF8String], value);
}

- (void)setStringValue:(NSString *)value forKey:(NSString *)key isObject:(BOOL)isObject {
  kv->saveS([key UTF8String], [value UTF8String], isObject);
}

- (HCacheValue *)getCacheValueForKey:(NSString *)key {
    auto value = kv->getValue([key UTF8String]);
    HCacheValueType typ = HCacheValueTypeNULL;
    id _value = nil;
    if (value.isInt()) {
        int v = value.getInt();
        typ = HCacheValueTypeInt;
        _value = [NSNumber numberWithInt:v];
    } else if (value.isBool()) {
        BOOL v = value.getBool();
        typ = HCacheValueTypeBOOL;
        _value = [NSNumber numberWithBool:v];
    } else if (value.isLong()) {
        long v = value.getLong();
        typ = HCacheValueTypeLong;
        _value = [NSNumber numberWithLong:v];
    } else if (value.isFloat()) {
        float v = value.getFloat();
        typ = HCacheValueTypeFloat;
        _value = [NSNumber numberWithFloat:v];
    } else if (value.isDouble()) {
        double v = value.getDouble();
        typ = HCacheValueTypeDouble;
        _value = [NSNumber numberWithDouble:v];
    } else if (value.isString()) {
        string v = value.getString();
        typ = HCacheValueTypeString;
        const char * c_v = v.c_str();
        _value = [NSString stringWithUTF8String:c_v];
    } else if (value.isJsonString()) {
        string v = value.getJsonString();
        typ = HCacheValueTypeJSONString;
        const char * c_v = v.c_str();
        _value = [NSString stringWithUTF8String:c_v];
    }
    return [HCacheValue cacheWithType:typ withValue:_value];
    
}

@end
