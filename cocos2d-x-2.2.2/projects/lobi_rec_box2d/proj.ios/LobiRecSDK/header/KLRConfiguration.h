//
//  KLRConfiguration.h
//  LobiRankingSDK
//

#import <Foundation/Foundation.h>

@interface KLRConfiguration : NSObject

@property (nonatomic, copy, setter=setClientID:) NSString *clientID;
@property (nonatomic, copy) NSString *accountBaseName;
@property (nonatomic, readonly) NSString* adPlatform;
@property (nonatomic, readonly) NSString* adPlatformId;

+ (instancetype)currentConfiguration;

- (NSString*)hostApplicationVersion;

- (void)setAdPlatform:(NSString*)adPlatform adPlatformId:(NSString*)adPlatformId;

@end
