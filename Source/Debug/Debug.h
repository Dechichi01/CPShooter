#pragma once

#define ENSURE ensure
#define VERIFY verify
#define CHECK check

#define DLOG(x, ...) UE_LOG(LogTemp, Log, TEXT(x), ##__VA_ARGS__)
#define WLOG(x, ...) UE_LOG(LogWarning, Log, TEXT(x), ##__VA_ARGS__)
