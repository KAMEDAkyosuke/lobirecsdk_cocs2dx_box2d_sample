//
//  KLRAPI.h
//  LobiRankingSDK
//

#import <UIKit/UIKit.h>

#import "KLRRanking.h"

typedef NS_ENUM(NSInteger, KLRAPIStatusCode){
    KLRAPIStatusCodeSuccess       = 0,
    KLRAPIStatusCodeNetworkError  = 100,
    KLRAPIStatusCodeResponseError = 101,
    KLRAPIStatusCodeFatalError    = 102
};

@interface KLRAPI : NSObject

+ (void)signupWithBaseName:(NSString *)baseName
                   handler:(void (^)(KLRAPIStatusCode code, id response))handler;

#pragma mark - update user data
// ユーザ名の変更
+ (void)updateUserName:(NSString *)name handler:(void (^)(KLRAPIStatusCode code, id response))handler;;

// ユーザアイコンの変更
+ (void)updateUserIcon:(UIImage *)icon handler:(void (^)(KLRAPIStatusCode code, id response))handler;;

#pragma mark - ranking
// ランキング送信
+ (void)sendRanking:(NSString *)rankingID
              score:(int64_t)score
            handler:(void (^)(KLRAPIStatusCode code, id response))handler;

// ランキング詳細取得
+ (void)getRanking:(NSString *)rankingID
              type:(KLRRankingRange)type
            origin:(KLRRankingCursorOrigin)origin
            cursor:(NSInteger)cursor
             limit:(NSInteger)limit
           handler:(void (^)(KLRAPIStatusCode code, id response))handler;

// すべてのランキングを取得する
+ (void)getRankingList:(KLRRankingRange)type
               handler:(void (^)(KLRAPIStatusCode code, id response))handler;

+ (void)getRankingList:(KLRRankingRange)type
                  user:(NSString*)uid
               handler:(void (^)(KLRAPIStatusCode code, id response))handler;

@end
