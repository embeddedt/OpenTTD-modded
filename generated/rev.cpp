/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file rev.cpp Autogenerated file with the revision and such of OpenTTD. */

#include "stdafx.h"
#include "core/bitmath_func.hpp"
#include "rev.h"

#include "safeguards.h"

/**
 * Is this version of OpenTTD a release version?
 * @return True if it is a release version.
 */
bool IsReleasedVersion()
{
	return HasBit(_openttd_newgrf_version, 19);
}

/**
 * The text version of OpenTTD's revision.
 * This will be either
 * - "<tag>", like "<major>.<minor>.<build>[-RC<rc>]",
 * - "<commitdate>-g<shorthash><modified>" in "master",
 * - "<commitdate>-<branch>-g<shorthash><modified>" in other branches, or
 * - "norev000", if the version is unknown.
 *
 * The major, minor and build are the numbers that describe releases of
 * OpenTTD (like 0.5.3). "-RC" is used to flag release candidates.
 *
 * <modified> shows a "M", if the binary is made from modified source code.
 */
const char _openttd_revision[] = "20220211-stock_jgr-g28709f67f9";

const char _openttd_release_version[] = "0.46.1";

/**
 * The text version of OpenTTD's build date.
 * Updating the build date in this file is the safest as it generally gets
 * updated for each revision in contrary to most other files that only see
 * updates when they are actually changed themselves.
 */
const char _openttd_build_date[] = __DATE__ " " __TIME__;

/**
 * The configure defines used to build OpenTTD
 */
const char _openttd_build_configure_defines[] = "NDEBUG WITH_DEMANGLE WITH_SIGACTION TTD_ENDIAN=TTD_LITTLE_ENDIAN UNIX WITH_PNG WITH_ZLIB WITH_SDL2 WITH_PERSONAL_DIR NO_THREADS WITH_ASSERT";

/**
 * The git revision hash of this version.
 */
const char _openttd_revision_hash[] = "28709f67f97cf0de573b8c6037e092bbfd01b5ee";

/**
 * The year of this version.
 */
const char _openttd_revision_year[] = "2022";

/**
 * Let us know if current build was modified. This detection
 * works even in the case when revision string is overridden by
 * --revision argument.
 * Value 0 means no modification, 1 is for unknown state
 * (compiling from sources without any version control software)
 * and 2 is for modified revision.
 */
const byte _openttd_revision_modified = 0;

/**
 * Indicate whether this is a tagged version.
 * If this is non-0, then _openttd_revision is the name of the tag,
 * and the version is likely a beta, release candidate, or real release.
 */
const byte _openttd_revision_tagged = 0;

/**
 * To check compatibility of BaNaNaS content, this version string is used.
 * It should never contain things like "beta", but only the release version
 * we are compatible with.
 */
const char _openttd_content_version[] = "12.0";

/**
 * The NewGRF revision of OTTD:
 * bits  meaning.
 * 24-31 major version + 16
 * 20-23 minor version
 *    19 1 if it is a release, 0 if it is not.
 *  0-18 used to be the SVN revision, now just last revision before switch to git
 *
 * The 19th bit is there so the development/betas/alpha, etc. leading to a
 * final release will always have a lower version number than the released
 * version, thus making comparisons on specific revisions easy.
 *
 * The + 16 for the major version is because we went from 1.11.0 to 12.0, dropping
 * the "patch" part of the version. To make sure "1.11.0" is smaller than "12.0", we
 * have to adjust the major by 16.
 */
/** 0 removed */
const uint32 _openttd_newgrf_version = (13 + 16) << 24 | 0 << 20 | 0 << 19 | 28004;
