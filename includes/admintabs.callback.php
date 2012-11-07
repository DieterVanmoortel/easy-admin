<?php

chdir($_SERVER['DOCUMENT_ROOT']);
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once DRUPAL_ROOT . '/includes/common.inc';
require_once DRUPAL_ROOT . '/includes/module.inc';

sleep(3);
$result['status'] = FALSE;
if($value = ltrim($_POST['value'], '/')) {
  exit($result);
  switch($value){
    case 'flush_caches':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);
      $result['status'] = la_flush_caches();
      
      break;
    case 'rebuild_menu':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);
      cache_clear_all('*', 'cache_menu', TRUE);
      $result['status'] = TRUE;
      break;
    case 'rebuild_css_js':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);
      cache_clear_all('*', 'cache_menu', TRUE);
      $result['status'] = TRUE;
      break;
    case 'translate':
      break;
  }
}
exit($result);







/**************** CALLBACK FUNCTIONS ************************************/

