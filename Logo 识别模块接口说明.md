Logo 识别模块接口说明
---

### 1.获取需要处理的视频地址和相关参数

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
{
	"URL_PATH":"{URL.josn}",
	"PARA_PATH":"{parameter.json}"
}	
```
### 2. 获取tag信息的json格式(这里只列出CLM模块所需的信息)
- 其中，返回tag信息的json格式及所需信息如下：
```json
{
	"code":0,
	"des":null,
	"list":
		[			
		{
		"filmTagId:"1430937373871000"
		"videoPath":"./1430937373871000.mp4"
		"adTime":"205.36",
		"adLength":"0.3922",
		"adWidth":"0.1726",
		"adX":"0.7803",
		"adY":"0.3736",
		"logoId":"12341824721947",
		"logoPath":"../1248124798.jpeg"
		},
		{
		"filmTagId:"1430937373871333"
		"videoPath":"./1430937373871333.mp4"
		"adTime":"205.36",
		"adLength":"0.3922",
		"adWidth":"0.1726",
		"adX":"0.7803",
		"adY":"0.3736",
		"logoId":"12341824721237",
		"logoPath":"../1248124723.jpeg"
		}
	]
}
```

### 3.设置匹配状态

返回json：
```
{
	"code":0,
	"des":null,
	"list":[{"match":"1"}]
} 
```