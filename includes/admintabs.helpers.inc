<?php
/**
 * @file
 * Helper functions
 */

/*
 * The content of the easy admin block
 */
function admintabs_block_render() {
  $default_tab_height = 100;
  $def_pad = 5;
  $small_tab_height = 40;

  $output = '<div id="admintabs">';
  $h = 205;
  // Primary & secondary actions
  $tasks = menu_local_tasks();

  // todo : make modules link directly to modules page ( e.g. )
  if ($tasks['tabs']['count'] || $tasks['actions']['count']) {
    $output .= '<div class="tab primary">';
    if (!empty($tasks['tabs']['output'])) {
      // unset the view tab in the frontend
      if (!path_is_admin($_GET['q'])) {
        foreach((array)$tasks['tabs']['output'] as $key => $value) {
          if(isset($value['#link']['path']) && $value['#link']['path'] == 'node/%/view'){
            unset($tasks['tabs']['output'][$key]);
          }
        }
      }
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
    $output .= '<div class="tab translate" style="top:' . $h . 'px;">';
    $output .= theme('translationlink');
    $output .= '</div>';
    $h += $small_tab_height +  $def_pad;
  }

  // Navigation menu
  $navitems = admintabs_default_navigation();
  if(!empty($navitems)){
    $output .= '<div class="tab navigate" style="top:' . $h . 'px;">';
    $output .= implode('', $navitems);
    $output .= '</div>';
    $h += $default_tab_height + $def_pad;
  }
  
  if(user_access('use admintab functions')) {
    // Administrator functions
    $default_functions = admintabs_default_functions();
    $functions = theme('item_list', array('items' => $default_functions));
    $output .= '<div class="tab tools" style="top:' . $h . 'px;">';
    $output .= $functions;
    $output .= '<div id="adminspinner" class="spinwrapper"><span id="spinner-msg"></span></div>';
    $output .= '</div>';
    $h += $default_tab_height + $def_pad;
  }

//  $custom_menu_tree = menu_tree_page_data(variable_get_value('admintabs-menu'));
//  $custom_menu_tree = menu_tree_page_data('menu-about-us-be-nl-');  // demo
//  $menu = menu_tree_output($custom_menu_tree);
//  $output .= '<div class="tab menu" style="top:' . $h . 'px;">';
//  $output .= drupal_render($menu);
//  $output .= '</div>';
//  $h += $default_tab_height + $def_pad;

  // log out
  $output .= '<div class="tab logout" style="top:' . $h . 'px;">';
  $output .= '<ul><li><span><a href="user/logout">Log out</a></span></li></ul>';
  $output .= '</div>';
  $h += $small_tab_height +  $def_pad;
  
  $output .= '</div>'; // close the admintabs div
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
    $external = (isset($options['process']) && $options['process'] == 'backend') ? TRUE : FALSE;
    $items[] = l($action['title'], $callback, array('external' => $external, 'attributes' => $options));
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
