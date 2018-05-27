# 基于N...开发

# 创建私钥，得到公钥

```csharp
RandomUtils.Random = new UnsecureRandom();
Key privateKey = new Key();//私钥
PubKey publicKey = privateKey.PubKey;
txb_public_key.Text = publicKey.GetAddress(Network.TestNet).ToString();
txb_private_key.Text = privateKey.ToString(Network.TestNet);//输出
```

A Bitcoin wallet must do the following:

1. Generate addresses.
2. Recognize transactions spent to these addresses.
3. Detect transactions, those are spending from these addresses.
4. Show the history of the transactions involving this wallet.
5. Handle reorgs.
6. Handle conflicts.
7. Dynamically calculate transaction fees.
8. Build and sign transactions.
9. Broadcast transactions.

[温国兵的随想录](https://dbarobin.com/blockchain/)  
[区块链钱包开发](https://medium.com/@robinwan/区块链钱包开发-b3ad79bb1c85)  
本文讲解了开发钱包的预备知识，包括第一是什么是钱包，以及相关的分类，第二是 RPC、JSON-RPC 以及 JSON，第三是了解区块链相关的基础知识，第四是掌握一门开发语言。接着浅谈了怎么样开发，最后列出了主流项目相关的 RPC 接口以及开源钱包项目。如果读者对钱包开发感兴趣，希望本文能够给读者一个指引。

20180527

通过密码设定来获取助记词：

Safe safe = Safe.Create\(out mnemonic, pw, walletFilePath, Config.Network\);

MCCBit

Password:AA

mnemonic:people relief fade phone unveil bracket change say enter term add worth

DotNetWallet:

password:Alpha2018

mnemonic: scan jazz seminar dog joke caution print hurdle purse merge grape impose

