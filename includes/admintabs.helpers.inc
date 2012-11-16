<?php
function admintabs_default_functions(){
  $actions = array(
    'flush_caches' => array(
      'title' => t('Flush Caches'),
      'attributes' => array(
        'process' => 'backend',
        'msg' => t('Flushing all caches'),
      ),
    ),
    'rebuild_menu' => array(
      'title' => t('Rebuild Menu'),
      'attributes' => array(
        'process' => 'backend',
        'msg' => t('Rebuilding Menu'),
      ),
    ),
    'rebuild_css_js' => array(
      'title' => t('Rebuild CSS & JS'),
      'attributes' => array(
        'process' => 'backend',
        'msg' => t('Rebuilding CSS & JS'),
      ),
    ),
    'run_cron' => array(
      'title' => t('Run cron'),
      'attributes' => array(
        'process' => 'backend',
        'msg' => t('Running Cron'),
      ),
    ),
    'admin/reports/dblog' => array(
      'title' => t('View Reports'),
    ),
  );

  foreach($actions as $callback => $action) {
    $options = isset($action['attributes']) ? $action['attributes'] : array();
    $items[] = l($action['title'], $callback, array('attributes' => $options));
  }
  return $items;
}


function admintabs_default_navigation(){
  $menutree = menu_build_tree('management');
  $menu = array_shift($menutree);
  $admin = $menu['below'];
  $items = array();
  foreach((array)$admin as $path => $rootmenu){
    if(!empty($rootmenu['below'])) {
      $items['root'][$rootmenu['link']['mlid']] = theme('parent_tab', $rootmenu['link']);
      $items[$rootmenu['link']['mlid']] = theme('child_tab', $rootmenu['below']);
    }
  }
  if($items['root']){
    $items['root'] = theme('item_list', array('items' => $items['root']));
    return $items;
  }
}
