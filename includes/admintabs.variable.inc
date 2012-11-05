<?php
/*
 * Implementing hook_variable_info
 */
function lazy_admin_variable_info($options) {

  $variables['lazy_admin_menu_options'] = array(
    'title' => t('Lazy Admin Links'),
    'type' => 'options',
    'group' => 'lazy_admin',
    'options callback' => '_lazy_admin_get_menulinks',
    'default' => array(),
  );
  $variables['quick_dev_hookds'] = array(
    'title' => t('Quick Dev Hookds'),
    'type' => 'options',
    'group' => 'lazy_admin',
    'options callback' => '_quick_dev_hooks',
    'default' => array(),
  );
  $variables['quick_dev_code'] = array(
    'title' => t('Quick Dev code'),
    'type' => 'string',
    'group' => 'lazy_admin',
  );

  return $variables;
}
/**
 * Implements hook_variable_group_info().
 */
function lazy_admin_variable_group_info() {
  $groups['lazy_admin'] = array(
    'title' => t('Lazy Admin'),
    'description' => t('Lazy Admin settings.'),
    'access' => 'use lazy admin',
  );
  return $groups;
}