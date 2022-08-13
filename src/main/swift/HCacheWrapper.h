//
//  HCacheWarper.h
//  HCacheExample
//
//  Created by 叶永平 on 2022/8/12.
//

#import <Foundation/Foundation.h>
#import "HCacheValue.h""

NS_ASSUME_NONNULL_BEGIN

@interface HCacheWrapper : NSObject

- (void)setupWithPath:(NSString *)path;

- (void)setBoolValue:(BOOL)value forKey:(NSString *)key;

- (void)setIntValue:(int)value forKey:(NSString *)key;

- (void)setLongValue:(long)value forKey:(NSString *)key;

- (void)setFloatValue:(float)value forKey:(NSString *)key;

- (void)setDoubleValue:(double)value forKey:(NSString *)key;

- (void)setStringValue:(NSString *)value forKey:(NSString *)key isObject:(BOOL)isObject;

- (HCacheValue *)getCacheValueForKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
