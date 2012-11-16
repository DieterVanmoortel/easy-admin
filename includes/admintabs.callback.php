<?php

chdir($_SERVER['DOCUMENT_ROOT']);
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once DRUPAL_ROOT . '/includes/common.inc';
require_once DRUPAL_ROOT . '/includes/module.inc';

$result['status'] = FALSE;
if($value = ltrim($_POST['value'], '/')) {
  switch($value){
    case 'flush_caches':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
      drupal_flush_all_caches();
      $result['status'] = TRUE;
      break;
    case 'rebuild_menu':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);
      cache_clear_all('*', 'cache_menu', TRUE);
      $result['status'] = TRUE;
      break;
    case 'rebuild_css_js':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
       _drupal_flush_css_js();
      registry_rebuild();
      drupal_clear_css_cache();
      drupal_clear_js_cache();
      $result['status'] = TRUE;
      break;
    case 'run_cron':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);
      $result['status'] = drupal_cron_run();
      break;
    case 'translate':
      break;
  }
}
exit(drupal_json_output($result));







/**************** CALLBACK FUNCTIONS ************************************/
function connect_to_db(){
  // get database settings & open connection
  $loc = $_SERVER['SERVER_NAME'];
  if (is_file($_SERVER['DOCUMENT_ROOT'] . '/sites/' . $loc . '/settings.php')) {
    $settings = $_SERVER['DOCUMENT_ROOT'] . '/sites/' . $loc . '/settings.php';
  }
  elseif(is_file($_SERVER['DOCUMENT_ROOT'] . '/sites/default/settings.php')) {
    $settings = $_SERVER['DOCUMENT_ROOT'] . '/sites/default/settings.php';
  }
  else {
    die('Could not open database settings file"\n"');
  }
  require_once($settings);
  $host = $databases['default']['default']['host'];
  $db = $databases['default']['default']['database'];
  $user = $databases['default']['default']['username'];
  $pass = $databases['default']['default']['password'];

  $con = mysql_connect($host, $user, $pass);
  $db = mysql_select_db($db);
}