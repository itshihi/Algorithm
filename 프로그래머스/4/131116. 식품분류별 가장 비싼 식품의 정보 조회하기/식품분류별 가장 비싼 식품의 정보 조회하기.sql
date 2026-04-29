SELECT
    CATEGORY, PRICE AS MAX_PRICE, PRODUCT_NAME
FROM
    FOOD_PRODUCT 
WHERE
    ((CATEGORY = '과자') || 
    (CATEGORY = '국') || 
    (CATEGORY = '김치') || 
    (CATEGORY = '식용유'))
    AND
    (PRICE IN
     (
    SELECT 
        MAX(PRICE)
    FROM 
        FOOD_PRODUCT
     GROUP BY
        CATEGORY
    ))
    
GROUP BY
    CATEGORY
    
ORDER BY
    MAX_PRICE DESC;