Logo 识别模块接口说明
---
###	class CLM (Commodity Logo Matching)
```c++
class CLM {
    json URLs;
    json parameters;//logopath, logid, remark
    Mat logo;
    Mat image;
public:
    void loadURL(string urlPath);
    void loadParameter(string parameterPath);
    json fetchTag();
    json setMatch(string filmTagId);
    void cutImage(string videoPath,string resolution,string adTime,string adLength,string adWidth,string adX,string adY);
    void setLogo();
    bool logoMatch();
};
```
### 运行说明

程序读入一个参数 `./configure.json`，从文件中获取`URL.json`文件和`./parameter.json`文件的访问目录，分别读入程序所需的url和各项参数。

- **以下三个文件需要以json格式根据需要自行编辑**
- 配置文件 URL.json
```json
{
	"CLM_FETCH_TAG_URL":"http://localhost:8080/VideoInfo/getallfilmtaginfo.do",
	"CLM_SET_MATCH_URL":"http://localhost:8080/VideoInfo/setmatch.do?"
}
```
- 配置文件parameters.json
```json
{
	"logoPath":"{logo文件目录}",
	"else":"{else}"
}
```
- 配置文件 configure.json:
```json
// configure.json
{
	"URL_PATH":"{URL.josn}",
	"PARA_PATH":"{parameter.json}"
}	
```

- 其中，返回tag信息的json格式及所需信息如下：
```json
{
	"code":0,
	"des":null,
	"list":
		[			
		{
		"adInfoId":"1430937373871000",
		"adInfoName":"18",
		"adInfoText":"/webapps/VideoInfo/hysxm/test/18.png",
		"movieId":"143083373749200001",
		"movieFileId":"143083373749200001",
		"filmTagId:"1430937373871000"
		"remark":"未知",
		"adTypeId":"01",
		"adUrl":"http://item.taobao.com/item.htm?id=21551052099",
		"adPath":"/image/ADogStory",
		"adTime":"205.36",
		"adLength":"0.3922",
		"adWidth":"0.1726",
		"adX":"0.7803",
		"adY":"0.3736",
		"state":2,
		"createTime":null,
		"createUserId":"http://h5.m.taobao.com/awp/core/detail.htm?id=4406",
		"adTagType":"01","tagInfoType":1
		},
		{
		"adInfoId":"1430950281045005",
		"adInfoName":"1",
		"adInfoText":"/VideoInfo/hysxm/test/1.png",
		"movieId":"143083373749200001",
		"movieFileId":"143083373749200001",
		"filmTagId":"143083373749200001"
		"remark":"未知",
		"adTypeId":"01",
		"adUrl":"http://item.taobao.com/item.htm?id=43962211888",
		"adPath":"/image/ADogStory",
		"adTime":"0.3",
		"adLength":"0.4572",
		"adWidth":"0.1695",
		"adX":"0.0272",
		"adY":"0.3662",
		"state":2,
		"createTime":null,
		"createUserId":"http://item.taobao.com/item.htm?id=43962211888",
		"adTagType":"01",
		"tagInfoType":1
		}
	]
}
```

### 函数说明
 - `void loadURL(string urlPath)`
	 - 以``urlPath`为目录，读入`URL.json`文件
 - `void loadParameter(string parameterPath)`
	 - 以`parameterPath`为目录，读入`parameter.json`文件
 - `json fetchTag()`
	 - 从`CLM_FETCH_TAG_URL`读入tag信息
 - `void cutImage(string videoPath,string resolution,string adTime,string adLength,string adWidth,string adX,string adY)`
	 - 根据参数从视频帧中截取图像
 - `void setLogo()`
	 - 根据logo目录设置logo
 - `bool logoMatch()`
	 - 计算是否匹配
 - `json setMatch(string filmTagId)`
	 - 若匹配，设置match