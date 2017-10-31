/*
 * Integrity header defitinion
 *
 * Copyright (C) 2016-2017, Milan Broz
 *
 * This file is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _CRYPTSETUP_INTEGRITY_H
#define _CRYPTSETUP_INTEGRITY_H

#include <stdint.h>

struct crypt_device;
struct device;
struct crypt_params_integrity;
struct volume_key;

/* dm-integrity helper */
#define SB_MAGIC	"integrt"
#define SB_VERSION	1

struct superblock {
	uint8_t magic[8];
	uint8_t version;
	int8_t log2_interleave_sectors;
	uint16_t integrity_tag_size;
	uint32_t journal_sections;
	uint64_t provided_data_sectors;
	uint32_t flags;
	uint8_t log2_sectors_per_block;
} __attribute__ ((packed));

int INTEGRITY_read_sb(struct crypt_device *cd, struct crypt_params_integrity *params);

int INTEGRITY_dump(struct crypt_device *cd, struct device *device, uint64_t offset);

int INTEGRITY_data_sectors(struct crypt_device *cd,
			   struct device *device, uint64_t offset,
			   uint64_t *data_sectors);
int INTEGRITY_key_size(struct crypt_device *cd);
int INTEGRITY_tag_size(struct crypt_device *cd,
		       const char *integrity,
		       const char *cipher_mode);

int INTEGRITY_format(struct crypt_device *cd,
		     const struct crypt_params_integrity *params,
		     struct volume_key *journal_crypt_key,
		     struct volume_key *journal_mac_key);

int INTEGRITY_activate(struct crypt_device *cd,
		       const char *name,
		       const struct crypt_params_integrity *params,
		       struct volume_key *vk,
		       struct volume_key *journal_crypt_key,
		       struct volume_key *journal_mac_key,
		       uint32_t flags);
#endif