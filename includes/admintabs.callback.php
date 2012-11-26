<?php

chdir($_SERVER['DOCUMENT_ROOT']);
define('DRUPAL_ROOT', getcwd());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once DRUPAL_ROOT . '/includes/common.inc';
require_once DRUPAL_ROOT . '/includes/module.inc';

$result['status'] = FALSE;

if(!isset($_POST['value'])) {
  $value = $_GET['q'];
  var_dump($value);
}else{
  $value = ltrim($_POST['value'], '/');
}
if($value) {
  switch($value){
    case 'flush_caches':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
      $core_tables = array(
        'cache',
        'cache_form',
        'cache_menu',
        'cache_path',
        'cache_filter',
        'cache_bootstrap',
        'cache_filter',
        'cache_page',
        'cache_l10n_update'
      );
      $other = module_invoke_all('flush_caches');
      $same = array_intersect($other, $core_tables);
      $tables = array_merge($core_tables, module_invoke_all('flush_caches'));
      foreach ($tables as $table) {
        try{
          db_delete($table)->execute();
        }
        catch(Exception $e){
          watchdog('clear cache', 'Unable to empty table');
        }
      }
      $result['status'] = TRUE;
      drupal_set_message('Caches flushed');
      break;
    case 'rebuild_menu':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_DATABASE);
      db_delete('cache_menu')->execute();
      $result['status'] = TRUE;drupal_set_message('Menu rebuild');
      break;
    case 'rebuild_css_js':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
       _drupal_flush_css_js();
      registry_rebuild();
      drupal_clear_css_cache();
      drupal_clear_js_cache();
      $result['status'] = TRUE;drupal_set_message('CSS & JS rebuild');
      break;
    case 'run_cron':
      drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);
      if(drupal_cron_run()){
        drupal_set_message('Cron ran succesfully');
      }   
      break;
  }
}
exit(drupal_json_output($result));
