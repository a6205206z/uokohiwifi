<?php 
$site_name = apAuthpuppyConfig::getConfigOption("site_name","");

if ($site_name != '') {
  sfContext::getInstance()->getResponse()->setTitle($site_name);
}

function isMobile()
{ 
    // 如果有HTTP_X_WAP_PROFILE则一定是移动设备
    if (isset ($_SERVER['HTTP_X_WAP_PROFILE']))
    {
        return true;
    } 
    // 如果via信息含有wap则一定是移动设备,部分服务商会屏蔽该信息
    if (isset ($_SERVER['HTTP_VIA']))
    { 
        // 找不到为flase,否则为true
        return stristr($_SERVER['HTTP_VIA'], "wap") ? true : false;
    } 
    // 脑残法，判断手机发送的客户端标志,兼容性有待提高
    if (isset ($_SERVER['HTTP_USER_AGENT']))
    {
        $clientkeywords = array ('nokia',
            'sony',
            'ericsson',
            'mot',
            'samsung',
            'htc',
            'sgh',
            'lg',
            'sharp',
            'sie-',
            'philips',
            'panasonic',
            'alcatel',
            'lenovo',
            'iphone',
            'ipod',
            'blackberry',
            'meizu',
            'android',
            'netfront',
            'symbian',
            'ucweb',
            'windowsce',
            'palm',
            'operamini',
            'operamobi',
            'openwave',
            'nexusone',
            'cldc',
            'midp',
            'wap',
            'mobile'
            ); 
        // 从HTTP_USER_AGENT中查找手机浏览器的关键字
        if (preg_match("/(" . implode('|', $clientkeywords) . ")/i", strtolower($_SERVER['HTTP_USER_AGENT'])))
        {
            return true;
        } 
    } 
    // 协议法，因为有可能不准确，放到最后判断
    if (isset ($_SERVER['HTTP_ACCEPT']))
    { 
        // 如果只支持wml并且不支持html那一定是移动设备
        // 如果支持wml和html但是wml在html之前则是移动设备
        if ((strpos($_SERVER['HTTP_ACCEPT'], 'vnd.wap.wml') !== false) && (strpos($_SERVER['HTTP_ACCEPT'], 'text/html') === false || (strpos($_SERVER['HTTP_ACCEPT'], 'vnd.wap.wml') < strpos($_SERVER['HTTP_ACCEPT'], 'text/html'))))
        {
            return true;
        } 
    } 
    return false;
} 
?>

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
    <?php include_http_metas() ?>
    <?php include_metas() ?>
    <?php include_title() ?>
    <link rel="shortcut icon" href="/favicon.ico" />
    <?php use_stylesheet('jQuery/themes/ui-lightness/jquery-ui-1.8.2.custom.css') ?>
    <?php use_javascript('jQuery/jquery-1.4.2.min.js') ?>
    <?php use_javascript('jQuery/jquery-ui-1.8.2.custom.min.js') ?>
    <?php include_javascripts() ?>
    <style type="text/css">  
    body {  
     padding: 0px;  
     margin: 0px;  
    }  
    .connecting input {
    background-color: #F8B551;
    border: 1px solid #F8B551;
    border-radius: 20px;
    outline: medium none;
    }
    </style>
    <!--
    <script type="text/javascript"> 
    var t=30;
    setInterval("refer()",1000); 
    function refer(){  
        if(t==1){ 
            $("form").submit();
        } 
        document.getElementById('show').innerHTML="System login .... please wait <span style='color:red'>"+t+"</span> s.";  
        t--; 
    } 
    </script>
    -->

    </head>
    <body>
    <script type="text/javascript"> 
    function pass(){
        $("form").submit();
    }
    </script>
    <?php if(isMobile()){ ?>
    <iframe id="iframepage" name="iframepage" frameBorder=0
     height="100%" scrolling="yes" width="100%" src="http://192.168.199.1:8081/router/mobile_index.html"></iframe>
    <div style="position: absolute; right:35%; top:80%;" class="connecting">
        <input onclick="pass()" style="width: 276px;height: 88px;font-size: 30px;" type="button" value="连接网络">
    </div>
     <?php 
     }
     else{
        ?>
    <iframe id="iframepage" name="iframepage" frameBorder=0
     height="100%" scrolling="yes" width="100%" src="http://192.168.199.1:8081/router/index.html"></iframe>
    <div style="position: absolute; right:20%; top:80%;" class="connecting">
        <input onclick="pass()" style="width: 138px;height: 44px;font-size: 18px;" type="button" value="连接网络">
    </div>
    <?php }?>
    <!--
    <div id="show" style="font-weight:bold;background-color: yellow; position: fixed; left: 0px; top: 30px; 
    padding: 10px 50px 10px 100px; color: rgb(63, 203, 192);
    filter:alpha(Opacity=80);-moz-opacity:0.8;opacity: 0.8;">System login .... please wait <span style="color:red">30</span> s.</div>
    -->
    <div style="display:none;position:fixed;left:0px;top:0px;">
        <div id="content">
            <?php if ($sf_user->hasFlash('notice')): ?>
                <div><?php echo __($sf_user->getFlash('notice')) ?></div>
            <?php endif; ?>
     
            <?php if ($sf_user->hasFlash('error')): ?>
                <div><?php echo __($sf_user->getFlash('error')) ?></div>
            <?php endif; ?>
            <?php echo $sf_content ?>
        </div>
    </div>
    </body>
</html>
