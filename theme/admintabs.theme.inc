<?php

function theme_parent_tab($vars) {
  $title = $vars['link_title'];
  return '<a class="parent-tab" mlid=' . $vars['mlid'] . '>' . $title . '</a>';
}

function theme_child_tab($vars) {
  foreach($vars as $var) {
    $plid = $var['link']['plid'];
    $items[] = l($var['link']['link_title'], $var['link']['link_path']);
  }
  return theme('item_list', array('items' => $items, 'attributes' => array('parent' => $plid, 'class' => 'child-tab')));
}
/*
 * Returns the translation tab html
 */
function theme_translationlink(){
  $output = '<span id="translate_link" class="icon"></span>';
  $translationlink = l(t('Translate'), 'translate', array('attributes' => array('process' => 'backend')));
  $output .= theme('item_list', array('items' => array($translationlink)));
  $output .= '<span id="translate-results"><ul><li><a>Result</a></li></ul></span>';
  return $output;
}