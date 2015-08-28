<?php 
$site_name = apAuthpuppyConfig::getConfigOption("site_name","");

if ($site_name != '') {
  sfContext::getInstance()->getResponse()->setTitle($site_name);
}
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
    <?php include_http_metas() ?>
    <?php include_metas() ?>
    <?php include_title() ?>
    <link rel="shortcut icon" href="/favicon.ico" />
    <?php use_stylesheet('jQuery/themes/ui-lightness/jquery-ui-1.8.2.custom.css') ?>
    <?php include_stylesheets() ?>
    <?php use_javascript('jQuery/jquery-1.4.2.min.js') ?>
    <?php use_javascript('jQuery/jquery-ui-1.8.2.custom.min.js') ?>
    <?php include_javascripts() ?>
    </head>
    <body>
    <h1>UOKO HIWIFI</h1>
    <div id="page" class="container ">

        <div id="content" class="span-16">
            <?php if ($sf_user->hasFlash('notice')): ?>
                <div class="notice"><?php echo __($sf_user->getFlash('notice')) ?></div>
            <?php endif; ?>
     
            <?php if ($sf_user->hasFlash('error')): ?>
                <div class="error"><?php echo __($sf_user->getFlash('error')) ?></div>
            <?php endif; ?>
            <?php echo $sf_content ?>
        </div>

    </div>
    </body>
</html>
