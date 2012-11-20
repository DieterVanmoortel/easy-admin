<?php
/**
 * @file
 * Helper functions
 */

/*
 * The content of the easy admin block
 */
function admintabs_block_render() {
  $output = '<div id="admintabs">';
  
  // Primary & secondary actions
  $tasks = menu_local_tasks();
  // todo : unset view tab on non admin pages
  // todo : make modules link directly to modules page ( e.o. )
  if ($tasks['tabs']['count'] || $tasks['actions']['count']) {
    $output .= '<div class="tab primary">';
    if (!empty($tasks['tabs']['output'])) {
      $output .= '<ul>';
      $output .= drupal_render($tasks['tabs']['output']);
      $output .= '</ul>';
    }
    if (!empty($tasks['actions']['output'])) {
      $output .= '<ul>';
      $output .= drupal_render($tasks['actions']['output']);
      $output .= '</ul>';
    }
    $output .= '</div>';
  }
  // translation
  if (user_access('translate content')) {
    drupal_add_js(drupal_get_path('module', 'admintabs') . '/plugins/babylon/babylon.js');
    $output .= '<div class="tab translate">';
    $output .= theme('translationlink');
    $output .= '</div>';
  }


  // Navigation menu
  $navitems = admintabs_default_navigation();
  if(!empty($navitems)){
    $output .= '<div class="tab navigate">';
    $output .= implode('', $navitems);
    $output .= '</div>';
  }
  
  // Administrator functions
  $default_functions = admintabs_default_functions();
  $functions = theme('item_list', array('items' => $default_functions));
  $output .= '<div class="tab tools">';
  $output .= $functions;
  $output .= '<div id="adminspinner" class="spinwrapper"><span id="spinner-msg"></span></div>';
  $output .= '</div>';

  $output .= '</div>'; // close the admintabs div
  // spinner
  return $output;
}

/*
 * Often used Administrator functions
 * Return array
 */
function admintabs_default_functions() {
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

  foreach ((array)$actions as $callback => $action) {
    $options = isset($action['attributes']) ? $action['attributes'] : array();
    $items[] = l($action['title'], $callback, array('attributes' => $options));
  }
  return $items;
}


/*
 * Navigation structure from the 'management' menu
 */
function admintabs_default_navigation() {
  $menutree = menu_build_tree('management');
  $menu = array_shift($menutree);
  $admin = $menu['below'];
  $items = array();
  foreach ((array)$admin as $path => $rootmenu) {
    if (!empty($rootmenu['below'])) {
      $items['root'][$rootmenu['link']['mlid']] = theme('parent_tab', $rootmenu['link']);
      $items[$rootmenu['link']['mlid']] = theme('child_tab', $rootmenu['below']);
    }
  }
  if (isset($items['root'])) {
    $items['root'] = theme('item_list', array('items' => $items['root']));
  }
  return $items;
}
