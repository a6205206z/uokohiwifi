<?php 
$site_name = apAuthpuppyConfig::getConfigOption("site_name","");

if ($site_name != '') {
  sfContext::getInstance()->getResponse()->setTitle($site_name);
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
    </style>
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
    </head>
    <body>
    <iframe id="iframepage" name="iframepage" frameBorder=0
     height="100%" scrolling="yes" width="100%" src="http://192.168.199.1:8081/2015/07/summer/"></iframe>

    <div id="show" style="font-weight:bold;background-color: yellow; position: fixed; left: 0px; top: 30px; 
    padding: 10px 50px 10px 100px; color: rgb(63, 203, 192);
    filter:alpha(Opacity=80);-moz-opacity:0.8;opacity: 0.8;">System login .... please wait <span style="color:red">30</span> s.</div>

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
