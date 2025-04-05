/*******************************************************************************
 * Copyright (C) 2025 by Landry Matthews
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Landry Matthews and the University of Colorado are not liable for
 * any misuse of this material.
 * ****************************************************************************/

/**
 * @file    log.h
 * @brief   h file for log macro
 *
 *
 * @author  Landry Matthews
 * @date    03/01/2025
 *
 */

/*
 * log.h - abstraction away from printf
 */
#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

#ifdef DEBUG
# define LOG printf
#else
# define LOG(...)
#endif

#endif /* LOG_H_ */
