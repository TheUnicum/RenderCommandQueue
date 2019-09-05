#pragma once

#define NONE
#define COMMA ,
#define COLON :
#define SEMICOLON ;
#define EXPAND(x) x

#define HZ_RENDER_PASTE2(a, b) a ## b
#define HZ_RENDER_PASTE(a, b) HZ_RENDER_PASTE2(a, b)
#define HZ_RENDER_UNIQUE(x) HZ_RENDER_PASTE(x, __LINE__)
#define HZ_RENDER_UNIQUE_HZR HZ_RENDER_UNIQUE(HZRenderCommand)
#define HZ_EXECUTE_FUNCTION Execute

//////////////////////////////////////////////////////////////////////////////////////////////////
#define DECL_ASSIGN(argID) auto& argID = ((HZ_RENDER_UNIQUE_HZR*)argBuffer)->argID
#define DECL_TYPE(argID) typename ::std::remove_const<typename ::std::remove_reference<decltype(argID)>::type>::type argID
#define DECL_INILIST(x) x(x)
#define DECL_IDENT(x) x
//////////////////////////////////////////////////////////////////////////////////////////////////

#define FOR_EACH_0(FUNC, HEADER, SEPAR, a0, a1, a2, a3, a4, a5) 
#define FOR_EACH_1(FUNC, HEADER, SEPAR, a0, a1, a2, a3, a4, a5) HEADER FUNC(a0)
#define FOR_EACH_2(FUNC, HEADER, SEPAR, a0, a1, a2, a3, a4, a5) HEADER FUNC(a0) SEPAR FUNC(a1)
#define FOR_EACH_3(FUNC, HEADER, SEPAR, a0, a1, a2, a3, a4, a5) HEADER FUNC(a0) SEPAR FUNC(a1) SEPAR FUNC(a2)
#define FOR_EACH_4(FUNC, HEADER, SEPAR, a0, a1, a2, a3, a4, a5) HEADER FUNC(a0) SEPAR FUNC(a1) SEPAR FUNC(a2) SEPAR FUNC(a3)
#define FOR_EACH_5(FUNC, HEADER, SEPAR, a0, a1, a2, a3, a4, a5) HEADER FUNC(a0) SEPAR FUNC(a1) SEPAR FUNC(a2) SEPAR FUNC(a3) SEPAR FUNC(a4)
#define FOR_EACH_6(FUNC, HEADER, SEPAR, a0, a1, a2, a3, a4, a5) HEADER FUNC(a0) SEPAR FUNC(a1) SEPAR FUNC(a2) SEPAR FUNC(a3) SEPAR FUNC(a4) SEPAR FUNC(a5)

#define  RENDER_IMPL_B_0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, N, ...) RENDER_IMPL_B(arg0, N, arg0, arg1, arg2, arg3, arg4, arg5)
#define  RENDER_IMPL_B_1(arg0, arg1, arg2, arg3, arg4, arg5, arg6, N, ...) RENDER_IMPL_B(arg1, N, arg0, arg1, arg2, arg3, arg4, arg5)
#define  RENDER_IMPL_B_2(arg0, arg1, arg2, arg3, arg4, arg5, arg6, N, ...) RENDER_IMPL_B(arg2, N, arg0, arg1, arg2, arg3, arg4, arg5)
#define  RENDER_IMPL_B_3(arg0, arg1, arg2, arg3, arg4, arg5, arg6, N, ...) RENDER_IMPL_B(arg3, N, arg0, arg1, arg2, arg3, arg4, arg5)
#define  RENDER_IMPL_B_4(arg0, arg1, arg2, arg3, arg4, arg5, arg6, N, ...) RENDER_IMPL_B(arg4, N, arg0, arg1, arg2, arg3, arg4, arg5)
#define  RENDER_IMPL_B_5(arg0, arg1, arg2, arg3, arg4, arg5, arg6, N, ...) RENDER_IMPL_B(arg5, N, arg0, arg1, arg2, arg3, arg4, arg5)
#define  RENDER_IMPL_B_6(arg0, arg1, arg2, arg3, arg4, arg5, arg6, N, ...) RENDER_IMPL_B(arg6, N, arg0, arg1, arg2, arg3, arg4, arg5)

//////////////////////////////////////////////////////////////////////////////////////////////////
#define RENDER(...) EXPAND(RENDER_IMPL_A(__VA_ARGS__, 6, 5, 4, 3, 2, 1, 0))
#define RENDER_IMPL_A(arg0, arg1, arg2, arg3, arg4, arg5, arg6, N, ...) RENDER_IMPL_B_##N(arg0, arg1, arg2, arg3, arg4, arg5, arg6, N, ...)
#define RENDER_IMPL_B(code, N, ...) \
	do{\
		struct HZ_RENDER_UNIQUE_HZR\
		{\
			HZ_RENDER_UNIQUE_HZR(EXPAND(FOR_EACH_##N(DECL_TYPE, NONE, COMMA, __VA_ARGS__)))\
					EXPAND(FOR_EACH_##N(DECL_INILIST, COLON, COMMA, __VA_ARGS__)) {}\
			\
			static void HZ_EXECUTE_FUNCTION(void* argBuffer)\
			{\
				EXPAND(FOR_EACH_##N(DECL_ASSIGN, NONE, SEMICOLON, __VA_ARGS__));\
				code\
			}\
			EXPAND(FOR_EACH_##N(DECL_TYPE, NONE, SEMICOLON, __VA_ARGS__));\
		};\
		{\
			auto mem = cmd_queue.Allocate(HZ_RENDER_UNIQUE_HZR::HZ_EXECUTE_FUNCTION, sizeof(HZ_RENDER_UNIQUE_HZR));\
			new (mem) HZ_RENDER_UNIQUE_HZR(EXPAND(FOR_EACH_##N(DECL_IDENT, NONE, COMMA, __VA_ARGS__)));\
		}\
	}while(0)


#define RENDER_S(...) { int self = 10; 	RENDER(self, __VA_ARGS__); }
