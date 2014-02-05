//
//  KLRRankingViewController.h
//  LobiRankingSDK
//

#import <UIKit/UIKit.h>

#import "NakamapRanking.h"
#import "KLRRanking.h"

typedef NS_ENUM(NSInteger, KLRRankingPage){
    KLRRankingPageRankingList = 0,
    KLRRankingPageADRecommend
};

@interface KLRRankingViewController : UIViewController

@property(nonatomic, assign) KLRRankingRange range;
@property(nonatomic, assign) KLRRankingPage page;

@end

