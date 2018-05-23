# 基于N...开发

# 创建私钥，得到公钥

```csharp
RandomUtils.Random = new UnsecureRandom();
Key privateKey = new Key();//私钥
PubKey publicKey = privateKey.PubKey;
txb_public_key.Text = publicKey.GetAddress(Network.TestNet).ToString();
txb_private_key.Text = privateKey.ToString(Network.TestNet);//输出
```



