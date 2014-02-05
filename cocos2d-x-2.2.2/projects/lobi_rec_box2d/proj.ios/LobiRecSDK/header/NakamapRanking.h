//
//  NakamapRanking.h
//  LobiRankingSDK
//

#import <Foundation/Foundation.h>

@interface NakamapRanking : NSObject

+ (instancetype)sharedInstance;

+ (BOOL)isReady;
+ (BOOL)isInstalled;
+ (BOOL)handleOpenURL:(NSURL *)url;

@end
