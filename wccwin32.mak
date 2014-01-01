# Watcom WMAKE Makefile for PDCurses library - Win32 Watcom C/C++ 10.6+
#
# Usage: wmake -f [win32\]wccwin32.mak [DEBUG=Y] [WIDE=Y] [UTF8=Y] [target]
#
# where target can be any of:
# [all|demos]

!ifdef %DT_SRCDIR
DT_SRCDIR	= $(%DT_SRCDIR)
!else
DT_SRCDIR	= .
!endif

!include $(DT_SRCDIR)\version.mif

osdir		= $(DT_SRCDIR)

CC		= wcc386
TARGET		= nt_win

CFLAGS		= /ei /zq /wx /i=$(DT_SRCDIR)

LIBEXE		= wlib /q /n /t

!include $(DT_SRCDIR)\watcom.mif

PLATFORM1	= Watcom C++ Win32a
PLATFORM2	= Open Watcom 1.6 for Win32a
ARCNAME		= pdc$(VER)_wcc_w32

# !include $(DT_SRCDIR)\makedist.mif
