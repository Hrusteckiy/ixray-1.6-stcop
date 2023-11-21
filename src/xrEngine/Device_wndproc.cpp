#include "stdafx.h"

bool CRenderDevice::on_message	(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT &result)
{
	switch (uMsg) {
		case WM_SYSKEYDOWN : {
			return true;
						   }
		case WM_ACTIVATE : 
		{
#ifdef INGAME_EDITOR
			if (editor()) {
				Device.b_is_Active	= TRUE;
				break;
			}
#endif // #ifdef INGAME_EDITOR
			ShowCursor(wParam == WA_INACTIVE);
			OnWM_Activate	(wParam, lParam);
			return			(false);
		}
		case WM_SETCURSOR : {
#ifdef INGAME_EDITOR
			if (editor())
				break;
#endif // #ifdef INGAME_EDITOR

			result			= 1;
			return			(true);
		}
		case WM_SYSCOMMAND : {
#ifdef INGAME_EDITOR
			if (editor())
				break;
#endif // #ifdef INGAME_EDITOR

			// Prevent moving/sizing and power loss in fullscreen mode
			switch (wParam) {
				case SC_MOVE:
				case SC_SIZE:
				case SC_MAXIMIZE:
				case SC_MONITORPOWER:
					result	= 1;
					return	(true);
			}
			return			(false);
		}
		case WM_CLOSE : {
			g_pEventManager->Event.Defer("KERNEL:disconnect"); 
			g_pEventManager->Event.Defer("KERNEL:quit");
#ifdef INGAME_EDITOR
			if (editor())
				break;
#endif // #ifdef INGAME_EDITOR

			result			= 0;
			return			(true);
		}
		case WM_HOTKEY: // prevent 'ding' sounds caused by Alt+key combinations
		case WM_SYSCHAR:
			result = 0;
			return true;
	}

	return					(false);
}
