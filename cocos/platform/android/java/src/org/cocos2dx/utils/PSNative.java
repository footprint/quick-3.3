package org.cocos2dx.utils;

import java.util.Vector;
import java.util.Locale;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;

import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Vibrator;
import android.telephony.TelephonyManager;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;

import android.util.Log;

public class PSNative {
	static Cocos2dxActivity mContext = null;
	static TelephonyManager mTelephonyManager = null;
	static Vibrator mVibrator = null;

	static PSDialog mCreatingDialog = null;
	static PSDialog mShowingDialog = null;
	static Vector<PSDialog> mShowingDialogs = null;

	static Drawable mAppIcon = null;

	static PSDialog.PSDialogListener mPSDialogListener = new PSDialog.PSDialogListener() {
		@Override
		public void onDismiss(PSDialog dialog) {
			showPreAlert();
		}
	};

	public static void init(Cocos2dxActivity context) {
		mContext = context;
		mTelephonyManager = (TelephonyManager) context
				.getSystemService(Context.TELEPHONY_SERVICE);
		mVibrator = (Vibrator) context
				.getSystemService(Context.VIBRATOR_SERVICE);

		mShowingDialogs = new Vector<PSDialog>();
	}

	public static void setAppIcon(Drawable icon) {
		// 当对话框需要带上图像时，调用该方法。null表示不带图像
		mAppIcon = icon;
	}

	public static void createAlert(final String title, final String message,
			final Vector<String> buttonTitles, final int listener) {
		if (mContext == null) {
			return;
		}

		mContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mCreatingDialog = new PSDialog(mContext).setCancelable(false)
						.setMessage(message).setTitle(title)
						.setLuaListener(listener)
						.setListener(mPSDialogListener).setIcon(mAppIcon);

				for (int i = 0; i < buttonTitles.size(); i++) {
					addAlertButton(buttonTitles.get(i));
				}

				if (mShowingDialog != null && mShowingDialog.isShowing()) {
					mShowingDialogs.add(mShowingDialog);
					mShowingDialog.hide();
				}

				mCreatingDialog.show();
				mShowingDialog = mCreatingDialog;
				mCreatingDialog = null;
			}
		});
	}

	@Deprecated
	/**
	 * this function will appear thread unsafe problem...
	 */
	public static void createAlert(final String title, final String message,
			final String defalutButtonTitle, final int listener) {
		if (mContext == null) {
			return;
		}

		mContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mCreatingDialog = new PSDialog(mContext).setCancelable(false)
						.setMessage(message).setTitle(title)
						.setLuaListener(listener)
						.setListener(mPSDialogListener);

				addAlertButton(defalutButtonTitle);

				if (mShowingDialog != null && mShowingDialog.isShowing()) {
					mShowingDialogs.add(mShowingDialog);
					mShowingDialog.hide();
				}

				mCreatingDialog.show();
				mShowingDialog = mCreatingDialog;
				mCreatingDialog = null;
			}
		});
	}

	public static int addAlertButton(final String buttonTitle) {
		if (mCreatingDialog == null)
			return 0;

		return mCreatingDialog.addAlertButton(buttonTitle);
	}

	public static void showAlert() {
		if (mCreatingDialog == null) {
			return;
		}

		mContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (mShowingDialog != null && mShowingDialog.isShowing()) {
					mShowingDialogs.add(mShowingDialog);
					mShowingDialog.hide();
				}

				mCreatingDialog.show();
				mShowingDialog = mCreatingDialog;
				mCreatingDialog = null;
			}
		});
	}

	public static void showAlertLua(final int luaFunctionId) {
		if (mCreatingDialog == null) {
			return;
		}

		mContext.runOnGLThread(new Runnable() {
			@Override
			public void run() {
				mCreatingDialog.setLuaListener(luaFunctionId);
				showAlert();
			}
		});
	}

	public static void cancelAlert() {
		if (mShowingDialog == null)
			return;

		mContext.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mShowingDialog.dismiss();
				mShowingDialog = null;
			}
		});
	}

	public static void showPreAlert() {
		if (mShowingDialogs.size() > 0) {
			mShowingDialog = mShowingDialogs.firstElement();
			mShowingDialogs.remove(0);
			mShowingDialog.show();
		} else {
			mShowingDialog = null;
		}
	}

	public static void openURL(String url) {
		if (mContext == null) {
			return;
		}
		Uri uri = Uri.parse(url);
		mContext.startActivity(new Intent(Intent.ACTION_VIEW, uri));
	}

	public static String getInputText(String title, String message,
			String defaultValue) {
		return "";
	}

	private static String getMacAddress() {
		WifiManager wifi = (WifiManager) mContext
				.getSystemService(Context.WIFI_SERVICE);
		WifiInfo info = wifi.getConnectionInfo();
		if (info == null)
			return null;
		return info.getMacAddress();
	}

	public static String getOpenUDID() {
		String id = null;
		if (mTelephonyManager != null) {
			id = mTelephonyManager.getDeviceId();
		}
		if (id == null) {
			id = getMacAddress();
		}
		if (id == null) {
			id = "";
		}
		return id;
	}

	public static int getNetworkStatus() {
		ConnectivityManager connManager = (ConnectivityManager)mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
	    NetworkInfo mWifi = connManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);

	    if (mWifi.isConnected()) {
	    	return 2;
	    }
	    
	    NetworkInfo mMobile = connManager.getNetworkInfo(ConnectivityManager.TYPE_MOBILE);
	    if (mMobile.isConnected()) {
	    	return 1;
	    }
	    return 2;
	}

	public static String getDeviceName() {
		return Build.USER;
	}

    public static String getAppVersion() {
    	Log.i("cocos2d-x", "getAppVersion ===1");
        PackageManager mngr = mContext.getPackageManager();
		String version = null;
		try {
			version = mngr.getPackageInfo(mContext.getPackageName(), 0).versionName;
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			version = "1.0.0";
			e.printStackTrace();
		}
		return version;
    }

    public static String getCountryCode() {
        return Locale.getDefault().getCountry();
    }

    public static String getLanguageCode() {
        return Locale.getDefault().getLanguage();
    }

	public static void vibrate(long time) {
		if (mVibrator == null) {
			return;
		}
		mVibrator.vibrate(time);
	}

	public static void vibrate(long[] pattern, int repeatcout) {
		if (mVibrator == null) {
			return;
		}
		mVibrator.vibrate(pattern, repeatcout);
	}

	public static Context getAppContext() {
		return mContext;
	}
}