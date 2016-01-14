<?php
/**
 * @file
 * Google Analytics Vimeo Video Tracking Admin Settings Form.
 */
 
namespace Drupal\google_analytics_vimeo\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;

class GoogleAnalyticsVimeoAdminSettingsForm extends ConfigFormBase {
  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'google_analytics_vimeo_settings';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $config = \Drupal::config('google_analytics_vimeo.admin_settings');
    $form['googleanalytics_vimeo_tracking'] = array(
      '#type' => 'fieldset',
      '#title' => t('Select Tracking'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $form['googleanalytics_vimeo_tracking']['googleanalytics_vimeo_tracking_options'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Enable Tracking'),
      '#options' => array(
        'googleanalytics_vimeo_progress25' => t('25% Progress'),
        'googleanalytics_vimeo_progress50' => t('50% Progress'),
        'googleanalytics_vimeo_progress75' => t('75% Progress'),
        'googleanalytics_vimeo_videoPlayed' => t('Video Played'),
        'googleanalytics_vimeo_videoPaused' => t('Video Paused'),
        'googleanalytics_vimeo_videoResumed' => t('Video Resumed'),
        'googleanalytics_vimeo_videoSeeking' => t('Video Seeking'),
        'googleanalytics_vimeo_videoCompleted' => t('Video Completed'),
      ),
    );
    $form['googleanalytics_vimeo_tracking']['googleanalytics_vimeo_tracking_options']['#default_value'] = array_keys(array_filter($config->get('visibility.tracking_options')));
    // Page specific visibility configurations.
    $account = \Drupal::currentUser();
    $php_access = $account->hasPermission('use PHP for vimeo tracking visibility');
    $visibility_mode = $config->get('visibility.visibility_mode');
    $pages = $config->get('visibility.request_path_pages');
    $options = array();
    $title = '';
    $description = '';
  
    if ($visibility_mode == GOOGLEANALYTICS_VIMEO_USE_PHP_FOR_TRACKING && !$php_access) {
      $form['googleanalytics_vimeo_visibility_options'] = array('#type' => 'value', '#value' => 1);
      $form['googleanalytics_vimeo_visibility_pages'] = array('#type' => 'value', '#value' => $pages);
    }
    else {
      $options = array(
        t('Every page except the listed pages'),
        t('The listed pages only'),
      );
      $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array(
        '%blog' => 'blog',
        '%blog-wildcard' => 'blog/*',
        '%front' => '<front>',
      ));
      if (\Drupal::moduleHandler()->moduleExists('php') && $php_access) {
        $options[] = t('Pages on which this PHP code returns <code>TRUE</code> (experts only)');
        $title = t('Pages or PHP code');
        $description .= ' ' . t('If the PHP option is chosen, enter PHP code between %php. Note that executing incorrect PHP code can break your Drupal site.', array('%php' => '<?php ?>'));
      }
      else {
        $title = t('Pages');
      }
    }
    $form['googleanalytics_vimeo_visibility_options'] = array(
      '#type' => 'radios',
      '#title' => t('Add Google Analytics Vimeo Video Tracking to specific pages'),
      '#options' => $options,
      '#default_value' => !empty($visibility_mode) ? $visibility_mode : 0,
    );
    $form['googleanalytics_vimeo_visibility_pages'] = array(
      '#type' => 'textarea',
      '#title' => $title,
      '#title_display' => 'invisible',
      '#default_value' => !empty($pages) ? $pages : '',
      '#description' => $description,
      '#wysiwyg' => FALSE,
      '#rows' => 10,
    );
	
	return parent::buildForm($form, $form_state);	
  }
  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    $values = $form_state->getValues();
    \Drupal::configFactory()->getEditable('google_analytics_vimeo.admin_settings')
    ->set('visibility.tracking_options', $values['googleanalytics_vimeo_tracking_options'])
    ->set('visibility.visibility_mode', $values['googleanalytics_vimeo_visibility_options'])
	->set('visibility.request_path_pages', $values['googleanalytics_vimeo_visibility_pages'])
    ->save();
    return parent::submitForm($form, $form_state);
  }
  /**
   * {@inheritdoc}
   */
  public function getEditableConfigNames() {
    return ['google_analytics_vimeo.admin_settings'];
  }

}