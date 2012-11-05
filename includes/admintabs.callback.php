<?php

chdir($_SERVER['DOCUMENT_ROOT']);
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once DRUPAL_ROOT . '/includes/common.inc';
require_once DRUPAL_ROOT . '/includes/module.inc';



$result['status'] = FALSE;
if($value = ltrim($_POST['value'], '/')) {
  $args = explode('/', $value);
  switch($args[0]){
    case 'flush_caches':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);
      $result['status'] = la_flush_caches();
      break;
    case 'rebuild_menu':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);
      cache_clear_all('*', 'cache_menu', TRUE);
      $result['status'] = TRUE;
      break;
    case 'translate':
      break;
  }
}
drupal_json_output($result);







/****************        CALLBACK FUNCTIONS ************************************/
/*
 * Flush caches
 */
function la_flush_caches(){
  $core = array('cache', 'cache_bootstrap', 'cache_filter', 'cache_page');
  $cache_tables = array_merge(module_invoke_all('flush_caches'), $core);
  foreach ($cache_tables as $table) {
    cache_clear_all('*', $table, TRUE);
  }
  return TRUE;
}