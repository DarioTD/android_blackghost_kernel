#
# Copyright (C) 2015 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#

#
# Makefile for Mediatek(R) MMC/SD host controller drivers
#

#add kernel source code path as head file search path
MTK_PLATFORM := $(subst ",,$(CONFIG_MTK_PLATFORM))
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/$(MTK_PLATFORM)/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat
ccflags-y += -I$(srctree)/drivers/misc/mediatek/base/power/$(MTK_PLATFORM)
ccflags-y += -I$(srctree)/drivers/misc/mediatek/base/power/include
#obj-$(CONFIG_MMC_MTK_PRO) += $(subst ",,$(CONFIG_MTK_PLATFORM))/

ifeq ($(CONFIG_MTK_HW_FDE_AES),y)
ccflags-y += -I$(srctree)/drivers/misc/mediatek/fde_aes/$(MTK_PLATFORM)
endif

ifeq ($(CONFIG_TRUSTONIC_TEE_SUPPORT),y)
include $(srctree)/drivers/misc/mediatek/gud/Makefile.include
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/rpmb/drrpmb/public
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/rpmb/drrpmb_gp/public
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/rpmb/tlrpmb/public
endif

ccflags-y += -I$(srctree)
#workaround for include mmc/card/queue.h and mmc/core/core.h
ccflags-y += -I$(srctree)/drivers
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/$(MTK_PLATFORM)

ifeq ($(CONFIG_MTK_PLATFORM), "mt6580")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/ComboA
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/ComboA/mt6580
obj-$(CONFIG_MMC_MTK_PRO) += ComboA/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt6735")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/ComboA
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/ComboA/mt6735
obj-$(CONFIG_MMC_MTK_PRO) += ComboA/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt6739")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6799
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6799/mt6739
obj-$(CONFIG_MMC_MTK_PRO) += mt6799/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt6757")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6757
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6757/mt6757
obj-$(CONFIG_MMC_MTK_PRO) += mt6757/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt6799")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6799
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6799/mt6799
obj-$(CONFIG_MMC_MTK_PRO) += mt6799/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt6758")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6758
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6758/mt6758
obj-$(CONFIG_MMC_MTK_PRO) += mt6758/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt6759")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6759
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6759/mt6759
obj-$(CONFIG_MMC_MTK_PRO) += mt6759/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt6763")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6763
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt6763/mt6763
obj-$(CONFIG_MMC_MTK_PRO) += mt6763/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt3886")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt3886
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt3886/mt3886
obj-$(CONFIG_MMC_MTK_PRO) += mt3886/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt6765")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/ComboA
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/ComboA/mt6765
obj-$(CONFIG_MMC_MTK_PRO) += ComboA/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt6761")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/ComboA
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/ComboA/mt6761
obj-$(CONFIG_MMC_MTK_PRO) += ComboA/
endif

ifeq ($(CONFIG_MTK_PLATFORM), "mt8167")
ccflags-y += -I$(srctree)/drivers/mmc/host/mediatek/mt8167
obj-y += mt8167/
endif
