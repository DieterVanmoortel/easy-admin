
<?php
/**
 * @file
 * Administration pages
 */

function admintabs_settings_form(&$form, &$form_state) {
  $form = array();
  $form['actions'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Show actions'),
      '#options' => array(1, 2, 3), 
  );
  $form['menu'] = array(
    '#markup' => 'Add a custom menu to the admin-toolbar',
  );
  return $form;
}