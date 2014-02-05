
#import <Foundation/Foundation.h>
#import <CoreVideo/CVOpenGLESTextureCache.h>
#import <CoreMedia/CoreMedia.h>
#import <AssetsLibrary/AssetsLibrary.h>
#import <AVFoundation/AVFoundation.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/glext.h>
#import <UIKit/UIKit.h>

/**
 *  ゲーム録画中のワイプ表示
 */
typedef NS_ENUM(NSUInteger, KLMLiveWipeStatus) {
    /**
     *  ワイプなし
     */
    KLMWipeStatusNone = 0,
    /**
     *  インカメラワイプ
     */
    KLMWipeStatusInCamera,
    /**
     *  アイコン
     */
    KLMWipeStatusIcon,
};

/**
 *  ゲーム録画ファイルの保存領域が100MB以下になった際に録画処理が停止され、userInfoにnilを格納して通知する通知名称です。
 */
extern NSString *const KLMDryingUpInStorageNotification;

/**
 *  ゲーム録画情報をサーバにPOSTした際に、userInfoに"url"をキーとしたhttp://play.lobi.coのプレビューURLを格納して通知する通知名称です。
 */
extern NSString *const KLMMovieCreatedNotification;

/**
 *  ゲーム録画ファイルをサーバにPOSTした際に、userInfoにnilを格納して通知する通知名称です。
 */
extern NSString *const KLMMovieUploadedNotification;

/**
 *  動画ポストviewControllerを閉じた時に、userInfoに動画のポスト処理の有無を格納して通知する通知名称です。
 */
extern NSString *const KLMDismissingPostVideoViewControllerNotification;

/**
  ゲーム録画エンジンクラス。シングルトンでインスタンスを提供します。
 
  OpenGLコンテキストとviewを受け、フレームバッファに描画されたゲームを動画ファイルとして保存します。
  ワイプの表示 / マイク入力 / マイクボリューム / ゲームボリューム / モザイク処理 などの制御を各プロパティにて行います。
 
  - ゲーム録画エンジンから送出される通知と通知名称
  - KLMDryingUpInStorageNotification
  ゲーム録画ファイルの保存領域が100MB以下になった際に録画処理が停止され、userInfoにnilを格納して通知する通知名称です。

  - KLMMovieCreatedNotification
  ゲーム録画情報をサーバにPOSTした際に、userInfoに"url"をキーとしたhttp://play.lobi.coのプレビューURLを格納して通知する通知名称です。
 
  - KLMMovieUploadedNotification
  ゲーム録画ファイルをサーバにPOSTした際に、userInfoにnilを格納して通知する通知名称です。
 */
@interface KLMVideoCapture : NSObject

/**
 *  シングルトンインスタンス。録画に付帯する機能はこのインスタンスから行います。
 */
+ (KLMVideoCapture *)sharedInstance;

/**
 *  録画中、録画停止中を提供します。
 */
@property (nonatomic, readonly, assign) BOOL    isCapturing;

/**
 *  録画中に表示するワイプの状態を設定します。
 */
@property (nonatomic, assign) KLMLiveWipeStatus liveWipeStatus;

/**
 *  録画中に表示するワイプのx座標を設定します。デバイス毎に設定する必要があります。
 */
@property (nonatomic, assign) CGFloat           wipePositionX;

/**
 *  録画中に表示するワイプのy座標を設定します。デバイス毎に設定する必要があります。
 */
@property (nonatomic, assign) CGFloat           wipePositionY;

/**
 *  録画中に表示するワイプのサイズを設定します。
 */
@property (nonatomic, assign) CGFloat           wipeSquareSize;

/**
 *  録画中のゲームボリュームの大きさを設定します。(0.0 - 1.0)
 */
@property (nonatomic, assign) CGFloat           gameSoundVolume;

/**
 *  録画中のマイク入力ボリュームの大きさを設定します。(0.0 - 1.0)
 */
@property (nonatomic, assign) CGFloat           micVolume;

/**
 *  録画中のマイク入力可否を設定します。
 */
@property (nonatomic, assign) BOOL              micEnable;

/**
 *  録画中このプロパティがtrueの間、ゲーム録画ファイルにモザイク処理がかかります。
 */
@property (nonatomic, assign) BOOL              preventSpoiler;

/**
 *  録画中このプロパティがtrueの間、ゲーム画面にワイプの表示がされません。
 */
@property (nonatomic, assign) BOOL              hideFaceOnPreview;

/**
　レンダリングループのフレームに対してゲーム録画ファイルに出力する回数を設定します。
 
  ex.

  capturePerFrame = 1 : 毎フレーム出力

  capturePerFrame = 4 : 4フレーム毎に1回出力
 */
@property (nonatomic, assign) NSUInteger        capturePerFrame;

/**
  Unityエンジンを使用する場合に利用します。このコールバックのパラメータから取得できるフレームバッファをgDefaultFBOに設定します。
 */
@property (nonatomic, copy) void(^activeFramebufferCallback)(GLuint);

/**
 *  OpenGLコンテキストとviewをゲーム録画エンジンに設定します。
 *
 *  @param context ゲームにて生成したコンテキストを設定します。
 *  @param glView  ゲームにて生成した描画先のviewを設定します。
 */
- (void)setCurrentContext:(EAGLContext*)context withGLView:(UIView*)glView;

/**
 *  ゲームにて生成した録画対象となるフレームバッファを設定します。
 *
 *  @param framebufferRef
 */
- (void)createFramebuffer:(GLuint)framebufferRef;

/**
 *  ゲーム録画フレームバッファを用意します。
 *
 *  @return ゲーム録画フレームバッファの用意に成功した場合trueを返します。
 */
- (BOOL)prepareFrame;

/**
 *  ゲームにて生成した録画対象となるフレームバッファからゲーム録画ファイルに出力します。
 *
 *  @param framebufferRef ゲームにて生成した録画対象となるフレームバッファ
 *
 *  @return フレームバッファをゲーム録画ファイルに出力成功した場合trueを返します。
 */
- (BOOL)appendFrame:(GLuint)framebufferRef;

/**
 *  ゲーム録画開始処理。ワイプ / マイク設定 / キャプチャフレーム設定は本処理より前に設定する必要があります。
 */
- (void)startCapturing;

/**
 *  ゲーム録画終了処理
 */
- (void)stopCapturing;

/**
 *  ゲーム録画ファイルが存在している場合trueを返します。
 *
 *  @return ゲーム録画ファイルが存在している場合trueを返します。
 */
- (BOOL)hasMovie;

@end
