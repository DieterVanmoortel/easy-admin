<?php
/**
 * default items in the tool tab
 * $actions[] = array('title', 'backend process')
 */
function lazy_admin_default_functions(){
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
/*
 * Default items in the navigation tab
 */
function lazy_admin_default_navigation(){
  $functions = array();
  $functions['content'] =  array(t('Content'));
  $functions['config'] =  array(t('Settings'));
  $functions['structure'] =  array(t('Structure'));
  $functions['people'] =  array(t('Users'));
  $functions['appearance'] =  array(t('Themes'));
  $menu_items = array();
  $menu = cache_get('lazy_admin_menu');
  if(!$menu){
    $menu_options = _lazy_admin_get_menulinks('extended');
    $selected_menu_options = array_filter(variable_get_value('lazy_admin_menu_options'));
    foreach($menu_options as $mid => $option){
      if(in_array($mid, $selected_menu_options)) {
        $menu_items[$mid] = $option;
      }
    }
    if($menu_items){
      cache_set('lazy_admin_menu', $menu_items);
    }
  }
  else{
    $menu_items = $menu->data;
  }
  $root_items = array();
  $items = array();
  foreach((array)$menu_items as $key => $item) {
    $root_items[] = l($item[0]->link_title, $item[0]->link_path, array('attributes' => array('class' => 'first level', 'name' => 'trigger-'.$key)));
    unset($item[0]);
    foreach($item as $link) {
      $items[$key][]= l($link->link_title, $link->link_path, array('attributes' => array('class' => 'second level')));
    }
  }
  return array('root' => $root_items, 'items' => $items);
}

/**
 * Frequently used actions
 * @param type $action
 */
function lazy_admin_actions($action){
  switch($action){
    case 'rebuild_menu':
      if(menu_rebuild()){drupal_set_message(t('Menu was reconstructed.'));}
      break;
    case 'flush_caches':
      drupal_flush_all_caches();
      drupal_set_message(t('Flushed all caches.'));
      break;
    case 'cron':
      if(drupal_cron_run()){drupal_set_message(t('Cron run succesfull.'));}
      break;
    case 'update':
      drupal_goto('update.php');
      break;
    case 'dblog':
      drupal_goto('admin/reports/dblog');
      break;
  }
  drupal_goto('<front>');
}

function _lazy_admin_get_menulinks($return = 'extended') {
    $query = db_select('menu_links', 'm')
          ->fields('m', array('p2','p3','link_path', 'link_title'))
          ->condition('p1', 1)
          ->condition('p4',0)
          ->condition('plid', array('0,1'), '<>');
    $return != 'extended' ? $query->condition('p3',0):'';
    $result = $query->execute()->fetchAll();
    foreach((array)$result as $key => $row){
      switch($return){
        case 'extended':
          $key != 0 ? $items[$row->p2][] = $row : '';
        break;

        default:
          $items[$row->p2] = $row->link_title;
        break;
      }
    }
    return (array)$items;
}
