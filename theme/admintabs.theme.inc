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