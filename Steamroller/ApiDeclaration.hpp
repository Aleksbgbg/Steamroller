#pragma once

#if defined(IN_ENGINE) || defined(IN_TEST)
#define EXPORT_API
#define EXPORT_API_INTERNAL_ONLY
#else
#ifdef EXPORT
#define EXPORT_API __declspec(dllexport)
#define EXPORT_API_NO_IMPORT __declspec(dllexport)
#else
#define EXPORT_API __declspec(dllimport)
#define EXPORT_API_NO_IMPORT
#endif
#endif