#import <Foundation/Foundation.h>

// ランキング取得設定
// ランキング期間
typedef NS_ENUM(NSUInteger, KLRRankingRange){
    KLRRankingRangeToday = 0,
    KLRRankingRangeWeek,
    KLRRankingRangeAll,
    KLRRankingRangeLastWeek,
};

// ランキングカーソル位置
typedef NS_ENUM(NSUInteger, KLRRankingCursorOrigin){
    KLRRankingCursorOriginTop = 0,
    KLRRankingCursorOriginSelf,
};

@interface KLRRanking : NSObject

+ (KLRRanking *)sharedRanking;

-(NSString *)rankingRangeToString:(KLRRankingRange) range;
-(NSString *)cursorOriginToString:(KLRRankingCursorOrigin) cursorOrigin;

@end
