
require("@nomicfoundation/hardhat-toolbox");

module.exports = {
  defaultNetwork: "hardhat",
  networks: {
    hardhat: {},
    myQuickNode: {
      url: "https://quick-quick-model.quiknode.pro/4347eba47aae2cfd9c73ccd76fc8a25cd2bb62bc/",
      flag: "flag{s0_y0u_c3n-gr4p}",
      accounts: [
        "QN_3351a720a8ea465c8fa718c9d34bc02a",
      api: [
	"9jfh892h8fu0i0-228982y0-h82hb2-2298282"
	],
	],
    },
  },
  solidity: "0.8.19",
};
