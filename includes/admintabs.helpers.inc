<?php
function admintabs_default_functions(){
  $actions = array();
  $actions['rebuild_menu'] = array(t('Rebuild Menu'), TRUE);
  $actions['flush_caches'] =  array(t('Flush Caches'), TRUE);
  $actions['cron'] =  array(t('Run Cron'), TRUE);
  $actions['update.php'] =  array(t('Run Updates'), FALSE);
  $actions['admin/reports/dblog'] =  array(t('View Reports'), FALSE);

  foreach($actions as $callback => $action) {
    $process = $action[1] ? 'backend' : 'frontend';
    $items[] = l($action[0], $callback, array('attributes' => array('process' => $process)));
  }
  return $items;
}


function admintabs_default_navigation(){
  $menutree = menu_build_tree('management');
  $menu = array_shift($menutree);
  $admin = $menu['below'];
  $adminsections = array(
    'admin/content',
    'admin/structure',
    'admin/config',
    'admin/people',
  );
  foreach($admin as $path => $rootmenu){
    if(!empty($rootmenu['below']) && in_array($rootmenu['link']['link_path'], $adminsections)) {
      $items['root'][$rootmenu['link']['mlid']] = theme('parent_tab', $rootmenu['link']);
      $items[$rootmenu['link']['mlid']] = theme('child_tab', $rootmenu['below']);
    }
  }
  $items['root'] = theme('item_list', array('items' => $items['root']));
  return $items;
}



















/**
 * default items in the tool tab
 * $actions[] = array('title', 'backend process')
 */
function lazy_admin_default_functions(){

  $actions['machine_name'] = array(
    'link' => t('blah'),
    'callback' => 'do_stuff',
    'attributes' => array(
      'process' => 'backend',
      'message' => 'Doing something',
    ),
  );


  // add a backend msg?
  $actions = array();
  $actions[] = array(t('Rebuild Menu'), TRUE);
  $actions['flush_caches'] =  array(t('Flush Caches'), TRUE);
  $actions['rebuild_css'] =  array(t('Rebuild CSS & JS'), TRUE);
  $actions['cron'] =  array(t('Run Cron'), TRUE);
  $actions['update.php'] =  array(t('Run Updates'), FALSE);
  $actions['admin/reports/dblog'] =  array(t('View Reports'), FALSE);

  foreach($actions as $callback => $action) {
    $process = $action[1] ? 'backend' : 'frontend';
    $items[] = l($action[0], $callback, array('attributes' => array('process' => $action[''])));
  }
  return $items;
}
