/*
 * DO NOT EDIT -- file generated from data in db.txt
 */

#include <linux/nl80211.h>
#include <net/cfg80211.h>
//#include "regdb.h"
#include "vos_regdb.h"

static const struct ieee80211_regdomain regdom_00 = {
	.alpha2 = "00",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 3, 20, 0),
		REG_RULE(2457, 2482, 40, 3, 20, 
			NL80211_RRF_PASSIVE_SCAN | 
			NL80211_RRF_NO_IBSS | 0),
		REG_RULE(2474, 2494, 20, 3, 20, 
			NL80211_RRF_PASSIVE_SCAN | 
			NL80211_RRF_NO_IBSS | 
			NL80211_RRF_NO_OFDM | 0),
		REG_RULE(5170, 5250, 80, 3, 20, 
			NL80211_RRF_PASSIVE_SCAN | 
			NL80211_RRF_NO_IBSS | 0),
		REG_RULE(5250, 5330, 80, 3, 20, 
			NL80211_RRF_PASSIVE_SCAN | 
			NL80211_RRF_NO_IBSS | 0),
		REG_RULE(5490, 5710, 80, 3, 20, 
			NL80211_RRF_PASSIVE_SCAN | 
			NL80211_RRF_NO_IBSS | 0),
		REG_RULE(5735, 5835, 80, 3, 20, 
			NL80211_RRF_PASSIVE_SCAN | 
			NL80211_RRF_NO_IBSS | 0),
		REG_RULE(57240, 63720, 2160, 0, 0, 0),
	},
	.n_reg_rules = 8
};

static const struct ieee80211_regdomain regdom_AE = {
	.alpha2 = "AE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_AF = {
	.alpha2 = "AF",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_AI = {
	.alpha2 = "AI",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_AL = {
	.alpha2 = "AL",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5150, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5350, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5470, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_AM = {
	.alpha2 = "AM",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 20, 0, 18, 0),
		REG_RULE(5250, 5330, 20, 0, 18, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_AN = {
	.alpha2 = "AN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_AR = {
	.alpha2 = "AR",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5590, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5650, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 6
};

static const struct ieee80211_regdomain regdom_AS = {
	.alpha2 = "AS",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5850, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_AT = {
	.alpha2 = "AT",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_AU = {
	.alpha2 = "AU",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_AW = {
	.alpha2 = "AW",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_AZ = {
	.alpha2 = "AZ",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 18, 0),
		REG_RULE(5250, 5330, 80, 0, 18, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_BA = {
	.alpha2 = "BA",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_BB = {
	.alpha2 = "BB",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 3, 23, 0),
		REG_RULE(5250, 5330, 80, 3, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 3, 30, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BD = {
	.alpha2 = "BD",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_BE = {
	.alpha2 = "BE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_BF = {
	.alpha2 = "BF",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 3, 24, 0),
		REG_RULE(5250, 5330, 80, 3, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 3, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 3, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_BG = {
	.alpha2 = "BG",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_BH = {
	.alpha2 = "BH",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 20, 0, 20, 0),
		REG_RULE(5250, 5330, 20, 0, 20, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 20, 0, 20, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BL = {
	.alpha2 = "BL",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BM = {
	.alpha2 = "BM",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_BN = {
	.alpha2 = "BN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 20, 0),
		REG_RULE(5250, 5330, 80, 0, 20, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 0, 20, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BO = {
	.alpha2 = "BO",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5250, 5330, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_BR = {
	.alpha2 = "BR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_BS = {
	.alpha2 = "BS",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_BT = {
	.alpha2 = "BT",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BY = {
	.alpha2 = "BY",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_BZ = {
	.alpha2 = "BZ",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 30, 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_CA = {
	.alpha2 = "CA",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5590, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5650, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 6
};

static const struct ieee80211_regdomain regdom_CF = {
	.alpha2 = "CF",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 40, 6, 24, 0),
		REG_RULE(5250, 5330, 40, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 40, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 40, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_CH = {
	.alpha2 = "CH",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
	},
	.n_reg_rules = 11
};

static const struct ieee80211_regdomain regdom_CI = {
	.alpha2 = "CI",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_CL = {
	.alpha2 = "CL",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 20, 0),
		REG_RULE(5250, 5330, 80, 0, 20, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 0, 20, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_CN = {
	.alpha2 = "CN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 23, 0),
		REG_RULE(5250, 5330, 80, 6, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
		REG_RULE(57240, 59400, 2160, 0, 28, 0),
		REG_RULE(59400, 63720, 2160, 0, 44, 0),
		REG_RULE(63720, 65880, 2160, 0, 28, 0),
	},
	.n_reg_rules = 7
};

static const struct ieee80211_regdomain regdom_CO = {
	.alpha2 = "CO",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_CR = {
	.alpha2 = "CR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 20, 6, 24, 0),
		REG_RULE(5250, 5330, 20, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 20, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 20, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_CX = {
	.alpha2 = "CX",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_CY = {
	.alpha2 = "CY",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_CZ = {
	.alpha2 = "CZ",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_DE = {
	.alpha2 = "DE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_DK = {
	.alpha2 = "DK",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_DM = {
	.alpha2 = "DM",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 23, 0),
		REG_RULE(5250, 5330, 80, 6, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_DO = {
	.alpha2 = "DO",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 23, 0),
		REG_RULE(5250, 5330, 80, 6, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_DZ = {
	.alpha2 = "DZ",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5670, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_EC = {
	.alpha2 = "EC",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 20, 6, 24, 0),
		REG_RULE(5250, 5330, 20, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 20, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 20, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_EE = {
	.alpha2 = "EE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_EG = {
	.alpha2 = "EG",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 20, 0, 23, 0),
		REG_RULE(5250, 5330, 20, 0, 23, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_ES = {
	.alpha2 = "ES",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_ET = {
	.alpha2 = "ET",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_FI = {
	.alpha2 = "FI",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_FM = {
	.alpha2 = "FM",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 3, 30, 0),
		REG_RULE(5170, 5250, 80, 3, 24, 0),
		REG_RULE(5250, 5330, 80, 3, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 3, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 3, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_FR = {
	.alpha2 = "FR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_GB = {
	.alpha2 = "GB",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_GD = {
	.alpha2 = "GD",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 3, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_GE = {
	.alpha2 = "GE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 18, 0),
		REG_RULE(5250, 5330, 80, 0, 18, 
			NL80211_RRF_DFS | 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_GF = {
	.alpha2 = "GF",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_GH = {
	.alpha2 = "GH",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_GL = {
	.alpha2 = "GL",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 20, 0, 23, 0),
		REG_RULE(5250, 5330, 20, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 20, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_GP = {
	.alpha2 = "GP",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_GR = {
	.alpha2 = "GR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_GT = {
	.alpha2 = "GT",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_GU = {
	.alpha2 = "GU",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 160, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_GY = {
	.alpha2 = "GY",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 30, 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_HK = {
	.alpha2 = "HK",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_HN = {
	.alpha2 = "HN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_HR = {
	.alpha2 = "HR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_HT = {
	.alpha2 = "HT",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_HU = {
	.alpha2 = "HU",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_ID = {
	.alpha2 = "ID",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5735, 5815, 20, 0, 30, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_IE = {
	.alpha2 = "IE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_IL = {
	.alpha2 = "IL",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_PI = {
	.alpha2 = "PI",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_IN = {
	.alpha2 = "IN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_IR = {
	.alpha2 = "IR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_IS = {
	.alpha2 = "IS",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_IT = {
	.alpha2 = "IT",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_JM = {
	.alpha2 = "JM",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_JO = {
	.alpha2 = "JO",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5735, 5835, 80, 0, 23, 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_JP = {
	.alpha2 = "JP",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(2474, 2494, 20, 0, 20, 
			NL80211_RRF_NO_OFDM | 0),
		REG_RULE(5170, 5250, 80, 0, 20, 
			NL80211_RRF_NO_OUTDOOR | 0),
		REG_RULE(5250, 5330, 80, 0, 20, 
			NL80211_RRF_NO_OUTDOOR | 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 20, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_KE = {
	.alpha2 = "KE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5490, 5570, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5775, 40, 0, 23, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_KH = {
	.alpha2 = "KH",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_KN = {
	.alpha2 = "KN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 23, 0),
		REG_RULE(5250, 5330, 80, 6, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 6, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5815, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_KR = {
	.alpha2 = "KR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 20, 0),
		REG_RULE(5250, 5330, 80, 6, 20, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5630, 80, 6, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5815, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_KP = {
	.alpha2 = "KP",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 20, 0),
		REG_RULE(5250, 5330, 80, 6, 20, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5630, 80, 6, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5815, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_KW = {
	.alpha2 = "KW",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_KY = {
	.alpha2 = "KY",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_KZ = {
	.alpha2 = "KZ",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
	},
	.n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_LB = {
	.alpha2 = "LB",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_LC = {
	.alpha2 = "LC",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 20, 0),
		REG_RULE(5250, 5330, 80, 6, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 6, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5815, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_LI = {
	.alpha2 = "LI",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
	},
	.n_reg_rules = 11
};

static const struct ieee80211_regdomain regdom_LK = {
	.alpha2 = "LK",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 20, 6, 24, 0),
		REG_RULE(5250, 5330, 20, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 20, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 20, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_LS = {
	.alpha2 = "LS",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_LT = {
	.alpha2 = "LT",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_LU = {
	.alpha2 = "LU",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_LV = {
	.alpha2 = "LV",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_MA = {
	.alpha2 = "MA",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_MC = {
	.alpha2 = "MC",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MD = {
	.alpha2 = "MD",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_ME = {
	.alpha2 = "ME",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MF = {
	.alpha2 = "MF",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MH = {
	.alpha2 = "MH",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_MK = {
	.alpha2 = "MK",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_MN = {
	.alpha2 = "MN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_MO = {
	.alpha2 = "MO",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_MP = {
	.alpha2 = "MP",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_MQ = {
	.alpha2 = "MQ",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MR = {
	.alpha2 = "MR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MT = {
	.alpha2 = "MT",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_MU = {
	.alpha2 = "MU",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_MV = {
	.alpha2 = "MV",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 20, 0),
		REG_RULE(5250, 5330, 80, 0, 20, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 0, 20, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MW = {
	.alpha2 = "MW",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_MX = {
	.alpha2 = "MX",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_MY = {
	.alpha2 = "MY",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 17, 0),
		REG_RULE(5250, 5330, 80, 6, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5815, 80, 6, 30, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_NA = {
	.alpha2 = "NA",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 20, 0, 0),
		REG_RULE(5170, 5250, 80, 23, 0, 0),
		REG_RULE(5250, 5330, 80, 23, 0, 0),
		REG_RULE(5490, 5710, 160, 30, 0, 0),
		REG_RULE(5735, 5835, 80, 33, 0, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_NG = {
	.alpha2 = "NG",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5250, 5330, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_NI = {
	.alpha2 = "NI",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_NL = {
	.alpha2 = "NL",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_NO = {
	.alpha2 = "NO",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_NP = {
	.alpha2 = "NP",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 20, 0),
		REG_RULE(5250, 5330, 80, 0, 20, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 0, 20, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_NZ = {
	.alpha2 = "NZ",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_OM = {
	.alpha2 = "OM",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_PA = {
	.alpha2 = "PA",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 23, 0),
		REG_RULE(5250, 5330, 80, 6, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_PE = {
	.alpha2 = "PE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_PF = {
	.alpha2 = "PF",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_PG = {
	.alpha2 = "PG",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_PH = {
	.alpha2 = "PH",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_PK = {
	.alpha2 = "PK",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 30, 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_PL = {
	.alpha2 = "PL",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_PM = {
	.alpha2 = "PM",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_PR = {
	.alpha2 = "PR",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_PS = {
	.alpha2 = "PS",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(4940, 4990, 40, 6, 33, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_PT = {
	.alpha2 = "PT",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_PW = {
	.alpha2 = "PW",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_PY = {
	.alpha2 = "PY",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_QA = {
	.alpha2 = "QA",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_RE = {
	.alpha2 = "RE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_RO = {
	.alpha2 = "RO",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_RS = {
	.alpha2 = "RS",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 3, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_RU = {
	.alpha2 = "RU",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 40, 0, 23, 0),
		REG_RULE(5250, 5330, 40, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5650, 5710, 40, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 40, 0, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_RW = {
	.alpha2 = "RW",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_SA = {
	.alpha2 = "SA",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_SE = {
	.alpha2 = "SE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_SG = {
	.alpha2 = "SG",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_SI = {
	.alpha2 = "SI",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_SK = {
	.alpha2 = "SK",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 12
};

static const struct ieee80211_regdomain regdom_SN = {
	.alpha2 = "SN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_SR = {
	.alpha2 = "SR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_SV = {
	.alpha2 = "SV",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 20, 3, 23, 0),
		REG_RULE(5250, 5330, 20, 3, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 20, 3, 30, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_SY = {
	.alpha2 = "SY",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
	},
	.n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_TC = {
	.alpha2 = "TC",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_TD = {
	.alpha2 = "TD",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_TG = {
	.alpha2 = "TG",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 40, 0, 23, 0),
		REG_RULE(5250, 5330, 40, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 40, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_TH = {
	.alpha2 = "TH",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_TN = {
	.alpha2 = "TN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_TR = {
	.alpha2 = "TR",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_TT = {
	.alpha2 = "TT",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_TW = {
	.alpha2 = "TW",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5590, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5650, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 6
};

static const struct ieee80211_regdomain regdom_TZ = {
	.alpha2 = "TZ",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5735, 5835, 80, 0, 30, 0),
	},
	.n_reg_rules = 2
};

static const struct ieee80211_regdomain regdom_UA = {
	.alpha2 = "UA",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 40, 0, 20, 0),
		REG_RULE(5250, 5330, 40, 0, 20, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5670, 40, 0, 20, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 40, 0, 20, 0),
		REG_RULE(57240, 65880, 2160, 0, 40, 
			NL80211_RRF_NO_OUTDOOR | 0),
	},
	.n_reg_rules = 6
};

static const struct ieee80211_regdomain regdom_UG = {
	.alpha2 = "UG",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_US = {
	.alpha2 = "US",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
		REG_RULE(5842, 5863, 5, 6, 30, 0),
		REG_RULE(5850, 5870, 10, 6, 30, 0),
		REG_RULE(5860, 5880, 10, 6, 30, 0),
		REG_RULE(5865, 5885, 20, 6, 30, 0),
		REG_RULE(5870, 5890, 10, 6, 30, 0),
		REG_RULE(5880, 5900, 10, 6, 30, 0),
		REG_RULE(5890, 5910, 10, 6, 30, 0),
		REG_RULE(5895, 5915, 20, 6, 30, 0),
		REG_RULE(5900, 5920, 10, 6, 30, 0),
		REG_RULE(5910, 5930, 10, 6, 30, 0),
		REG_RULE(57240, 63720, 2160, 0, 40, 0),
	},
	.n_reg_rules = 16
};

static const struct ieee80211_regdomain regdom_UY = {
	.alpha2 = "UY",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_UZ = {
	.alpha2 = "UZ",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 20, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 3
};

static const struct ieee80211_regdomain regdom_VC = {
	.alpha2 = "VC",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_VE = {
	.alpha2 = "VE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 23, 0),
		REG_RULE(5250, 5330, 80, 6, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_VI = {
	.alpha2 = "VI",
	.reg_rules = {
		REG_RULE(2402, 2472, 40, 0, 30, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_VN = {
	.alpha2 = "VN",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_VU = {
	.alpha2 = "VU",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_WF = {
	.alpha2 = "WF",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_WS = {
	.alpha2 = "WS",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 40, 0, 23, 0),
		REG_RULE(5250, 5330, 40, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 40, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_YE = {
	.alpha2 = "YE",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
	},
	.n_reg_rules = 1
};

static const struct ieee80211_regdomain regdom_YT = {
	.alpha2 = "YT",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

static const struct ieee80211_regdomain regdom_ZA = {
	.alpha2 = "ZA",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 6, 24, 0),
		REG_RULE(5250, 5330, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5730, 80, 6, 24, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5735, 5835, 80, 6, 30, 0),
	},
	.n_reg_rules = 5
};

static const struct ieee80211_regdomain regdom_ZW = {
	.alpha2 = "ZW",
	.reg_rules = {
		REG_RULE(2402, 2482, 40, 0, 20, 0),
		REG_RULE(5170, 5250, 80, 0, 23, 0),
		REG_RULE(5250, 5330, 80, 0, 23, 
			NL80211_RRF_DFS | 0),
		REG_RULE(5490, 5710, 80, 0, 30, 
			NL80211_RRF_DFS | 0),
	},
	.n_reg_rules = 4
};

const struct ieee80211_regdomain *reg_regdb[] = {
	&regdom_00,
	&regdom_AE,
	&regdom_AF,
	&regdom_AI,
	&regdom_AL,
	&regdom_AM,
	&regdom_AN,
	&regdom_AR,
	&regdom_AS,
	&regdom_AT,
	&regdom_AU,
	&regdom_AW,
	&regdom_AZ,
	&regdom_BA,
	&regdom_BB,
	&regdom_BD,
	&regdom_BE,
	&regdom_BF,
	&regdom_BG,
	&regdom_BH,
	&regdom_BL,
	&regdom_BM,
	&regdom_BN,
	&regdom_BO,
	&regdom_BR,
	&regdom_BS,
	&regdom_BT,
	&regdom_BY,
	&regdom_BZ,
	&regdom_CA,
	&regdom_CF,
	&regdom_CH,
	&regdom_CI,
	&regdom_CL,
	&regdom_CN,
	&regdom_CO,
	&regdom_CR,
	&regdom_CX,
	&regdom_CY,
	&regdom_CZ,
	&regdom_DE,
	&regdom_DK,
	&regdom_DM,
	&regdom_DO,
	&regdom_DZ,
	&regdom_EC,
	&regdom_EE,
	&regdom_EG,
	&regdom_ES,
	&regdom_ET,
	&regdom_FI,
	&regdom_FM,
	&regdom_FR,
	&regdom_GB,
	&regdom_GD,
	&regdom_GE,
	&regdom_GF,
	&regdom_GH,
	&regdom_GL,
	&regdom_GP,
	&regdom_GR,
	&regdom_GT,
	&regdom_GU,
	&regdom_GY,
	&regdom_HK,
	&regdom_HN,
	&regdom_HR,
	&regdom_HT,
	&regdom_HU,
	&regdom_ID,
	&regdom_IE,
	&regdom_IL,
	&regdom_PI,
	&regdom_IN,
	&regdom_IR,
	&regdom_IS,
	&regdom_IT,
	&regdom_JM,
	&regdom_JO,
	&regdom_JP,
	&regdom_KE,
	&regdom_KH,
	&regdom_KN,
	&regdom_KR,
	&regdom_KP,
	&regdom_KW,
	&regdom_KY,
	&regdom_KZ,
	&regdom_LB,
	&regdom_LC,
	&regdom_LI,
	&regdom_LK,
	&regdom_LS,
	&regdom_LT,
	&regdom_LU,
	&regdom_LV,
	&regdom_MA,
	&regdom_MC,
	&regdom_MD,
	&regdom_ME,
	&regdom_MF,
	&regdom_MH,
	&regdom_MK,
	&regdom_MN,
	&regdom_MO,
	&regdom_MP,
	&regdom_MQ,
	&regdom_MR,
	&regdom_MT,
	&regdom_MU,
	&regdom_MV,
	&regdom_MW,
	&regdom_MX,
	&regdom_MY,
	&regdom_NA,
	&regdom_NG,
	&regdom_NI,
	&regdom_NL,
	&regdom_NO,
	&regdom_NP,
	&regdom_NZ,
	&regdom_OM,
	&regdom_PA,
	&regdom_PE,
	&regdom_PF,
	&regdom_PG,
	&regdom_PH,
	&regdom_PK,
	&regdom_PL,
	&regdom_PM,
	&regdom_PR,
	&regdom_PS,
	&regdom_PT,
	&regdom_PW,
	&regdom_PY,
	&regdom_QA,
	&regdom_RE,
	&regdom_RO,
	&regdom_RS,
	&regdom_RU,
	&regdom_RW,
	&regdom_SA,
	&regdom_SE,
	&regdom_SG,
	&regdom_SI,
	&regdom_SK,
	&regdom_SN,
	&regdom_SR,
	&regdom_SV,
	&regdom_SY,
	&regdom_TC,
	&regdom_TD,
	&regdom_TG,
	&regdom_TH,
	&regdom_TN,
	&regdom_TR,
	&regdom_TT,
	&regdom_TW,
	&regdom_TZ,
	&regdom_UA,
	&regdom_UG,
	&regdom_US,
	&regdom_UY,
	&regdom_UZ,
	&regdom_VC,
	&regdom_VE,
	&regdom_VI,
	&regdom_VN,
	&regdom_VU,
	&regdom_WF,
	&regdom_WS,
	&regdom_YE,
	&regdom_YT,
	&regdom_ZA,
	&regdom_ZW,
};

int reg_regdb_size = ARRAY_SIZE(reg_regdb);
