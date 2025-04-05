#pragma once

#include <d3d9.h>

namespace gui
{
	//const
	constexpr int WIDTH = 500;
	constexpr int HEIGHT = 300;

	inline bool exit = true;

	//winapi vars
	inline HWND window = nullptr;
	inline WNDCLASSEXA windowClass = {};

	//movement	
	inline POINTS position = {};

	//directx state vars
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = {};

	//handle window creation and destruction
	void createHWindow(
		const char* windowName,
		const char* className) noexcept;
	void destroyHWindow() noexcept;
	

	//handle device creation n destruction
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	//handle ImGui creation and destruction
	void CreateImGui() noexcept;
	void DerstroyImGui() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;


}

