<?php
/**
 * @file
 * All theming functions defined in hook_theme
 */

/*
 * A tab that triggers subtabs when clicked
 */
function theme_parent_tab($vars) {
  $title = $vars['link_title'];
  return '<a class="parent-tab" mlid=' . $vars['mlid'] . '>' . $title . '</a>';
}

/*
 * Tabs triggered by clicking a parent
 */
function theme_child_tab($vars) {
  foreach ((array)$vars as $var) {
    $plid = $var['link']['plid'];
    $items[] = l($var['link']['link_title'], $var['link']['link_path']);
  }
  return theme('item_list', array('items' => $items, 'attributes' => array('parent' => $plid, 'class' => 'child-tab')));
}
/*
 * Babylon tab html
 */
function theme_translationlink() {
  $output = '';
  $translationlink = l(t('Select text to translate'), '#', array('attributes' => array('process' => 'none', 'class' => array('translate-trigger'))));
  $output .= theme('item_list', array('items' => array($translationlink)));
  $output .= '<span id="translate-options"></span>';
  return $output;
}
